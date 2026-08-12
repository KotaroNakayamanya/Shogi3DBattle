#include"DX12.h"

#include"Application.h"
#include<algorithm>
#include<cassert>
#include"WorldMat.h"
#include"I_Vertices.h"
#include<d3dcompiler.h>
#include"BasicTexType.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite.lib")

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    // デバッグ有効化
    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer;

        HRESULT result;

        result = D3D12GetDebugInterface(IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));
        assert(SUCCEEDED(result));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期処理
void DX12::InitDX12()
{
    _dxgiFactory = std::make_unique<DXGIFactory>();                           // DXGIファクトリー作成
    _device      = std::make_unique<Device>     (_dxgiFactory->GetAdapter()); // デバイス作成

    _cmdAllocator = _device->CreateCmdAllocator();                    // コマンドアロケータ作成
    _cmdList      = _device->CreateCmdList     (_cmdAllocator.Get()); // コマンドリスト作成
    _cmdQueue     = _device->CreateCmdQueue    ();                    // コマンドキュー作成

    _swapChain = _dxgiFactory->CreateSwapChain(_cmdQueue.Get()); // スワップチェーン作成

    _fenceVal = 0;                            // フェンス値初期値セット
    _fence = _device->CreateFence(_fenceVal); // フェンス作成
    
    CreateBuff(); // バッファ系作成
    CreateHeap(); // ヒープ作成
    CreateView(); // ビュー作成
    
    _rootSignature = _device->CreateRootSignature(_csuHeap.get()); // ルートシグネチャオブジェクト作成
    _vShader = CreateShader(L"VertexShader.hlsl", "VShader", "vs_5_1"); // 頂点シェーダー作成
    _pShader = CreateShader(L"PixelShader.hlsl",  "PShader", "ps_5_1"); // ピクセルシェーダー作成

    
    _pipeline = _device->CreatePipeline( // パイプラインオブジェクト作成
        _rootSignature.Get(), // ルートシグネチャ
        _vShader.Get(),       // 頂点シェーダ
        _pShader.Get());     // ピクセルシェーダ
    
    CreateDrawArea(); // 描画領域系作成
    
    CreateD2D(); // DirectX11系作成 

    WriteToBuff(); // バッファに書き込み

    CreateRenderTex(); // レンダーテクスチャ作成
}



// バッファ系作成
void DX12::CreateBuff()
{
    auto& app = Application::GetInstance();
    
    auto gameObjects = app.GetGameObjects();
    auto allVertIndices = gameObjects->GetAllVertIndices();

    // バックバッファ作成
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    _swapChain->GetDesc(&swapChainDesc);
    auto backBuffNum = swapChainDesc.BufferCount;
    _backBuffs.resize(backBuffNum);
    for (unsigned int i = 0; i < backBuffNum; i++)
    {
        _swapChain->GetBuffer(
            i,
            IID_PPV_ARGS(_backBuffs[i].ReleaseAndGetAddressOf()));
    }

    // デプスステンシルバッファ作成
    D3D12_RESOURCE_DESC backBuffDesc;
    backBuffDesc = _backBuffs[0]->GetDesc();
    auto widthSize  = static_cast<unsigned int>(backBuffDesc.Width);
    auto heightSize = static_cast<unsigned int>(backBuffDesc.Height);
    _dsBuff = _device->CreateBuff(widthSize, heightSize, BuffType::DEPTH_STENCIL);

    // コンスタントバッファ作成
    auto allGameObjects = gameObjects->GetAllGameObjects();
    unsigned int worldMatNum, viewProjNum, totalMatNum;
    worldMatNum = static_cast<unsigned int>(allGameObjects.size());
    viewProjNum = 1;
    totalMatNum = worldMatNum + viewProjNum;
    widthSize  = (sizeof(DirectX::XMMATRIX)*totalMatNum + 0xff) & ~0xff; // 256アラインメント
    heightSize = 1;
    _constBuff = _device->CreateBuff(widthSize, heightSize, BuffType::CONSTANT);

    // 頂点バッファ作成
    widthSize = 0;
    for(auto& shogiObj : allGameObjects) widthSize += sizeof(Vert) * static_cast<unsigned int>(shogiObj->GetVertices()->GetDatas().size());
    heightSize = 1;
    _vertBuff = _device->CreateBuff(widthSize, heightSize, BuffType::VERTEX);

    // 頂点インデックスバッファ作成
    widthSize = 0;
    for(auto& vertIndices : allVertIndices) widthSize += sizeof(unsigned short) * static_cast<unsigned int>(vertIndices->GetDatas().size());
    heightSize = 1;
    _idxBuff = _device->CreateBuff(widthSize, heightSize, BuffType::INDEX);

    // 木材テクスチャバッファ作成
    auto textures = app.GetTextures();
    auto woodTexs = textures->GetWoodTextures();
    auto woodTexNum = static_cast<unsigned int>(woodTexs.size());
    for (unsigned int i = 0; i < woodTexNum; i++)
    {
        widthSize  = woodTexs[i]->GetWidth();
        heightSize = woodTexs[i]->GetHeight();
        _woodTexBuffs.push_back(_device->CreateBuff(widthSize, heightSize, BuffType::TEXTURE));
    }

    // 将棋オブジェクト種類ごとのテクスチャバッファ作成
    widthSize  = 256;
    heightSize = 256;
    unsigned int pieceTextureNum = 8;
    for (unsigned int i = 0; i < pieceTextureNum; i++)
    {
        // 駒用テクスチャバッファ作成
        _shogiObjTexBuffs.push_back(_device->CreateBuff(widthSize, heightSize, BuffType::RENDER_TEX));
    }
    auto designTextures = textures->GetDesignTextures();
    auto designTextureNum   = static_cast<unsigned int>(designTextures.size());
    for (unsigned int i = 0; i < designTextureNum; i++)
    {
        // 駒以外のオブジェクトごとのテクスチャバッファ作成
        _shogiObjTexBuffs.push_back(_device->CreateBuff(widthSize, heightSize, BuffType::TEXTURE));
    }

    // エフェクト用テクスチャバッファ作成
    auto effectTexs = textures->GetEffectTextures();
    widthSize  = 256;
    heightSize = 256;
    for (auto& effectTex : effectTexs)
    {
        _effectTexBuffs.push_back(_device->CreateBuff(widthSize, heightSize, BuffType::TEXTURE));
    }
    
}

// ヒープ作成
void DX12::CreateHeap()
{
    // バックバッファRTVヒープ作成
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    _swapChain->GetDesc(&swapChainDesc);
    auto backBuffNum = swapChainDesc.BufferCount;
    _rtvHeap = _device->CreateHeap(backBuffNum, HeapType::RTV);


    // DSVヒープ作成
    _dsvHeap = _device->CreateHeap(1, HeapType::DSV);

    // CSUヒープ作成
    auto& app = Application::GetInstance();
    auto textures = app.GetTextures();
    unsigned int woodTexNum      = static_cast<unsigned int>(textures->GetWoodTextures().size());
    unsigned int designTexNum    = static_cast<unsigned int>(textures->GetDesignTextures().size());
    unsigned int pieceTexNum     = 8;
    unsigned int effectTexNum    = static_cast<unsigned int>(textures->GetEffectTextures().size());
    unsigned int cbvNum = 1;
    unsigned int srvNum = woodTexNum + designTexNum + pieceTexNum + effectTexNum;
    unsigned int uavNum = 0;
    _csuHeap = _device->CreateCSUHeap(cbvNum, srvNum, uavNum, HeapType::CSU);

    // 駒ごとの文字テクスチャ作成用RTVヒープ
    _texRTVHeap = _device->CreateHeap(pieceTexNum, HeapType::RTV);
}

// ビュー作成
void DX12::CreateView()
{
    // バックバッファ用RTV作成
    for (UINT i = 0; i < _rtvHeap->GetDescNum(); i++)
        _device->CreateView(_rtvHeap.get(), i, _backBuffs[i].Get(), View::RTV);

    // DSV作成
    for (UINT i = 0; i < _dsvHeap->GetDescNum(); i++)
        _device->CreateView(_dsvHeap.get(), i, _dsBuff.Get(), View::DSV);

    // CBV作成
    for (UINT i = 0; i < _csuHeap->GetCBVNum(); i++)
        _device->CreateCSUView(_csuHeap.get(), i, _constBuff.Get(), View::CBV);

    // 以下、テクスチャのSRVを作成する
    auto textures = Application::GetInstance().GetTextures();
    unsigned int srvIdx = 0;

    // 木材テクスチャ用SRV作成
    auto woodTexs = textures->GetWoodTextures();
    auto woodTexNum = static_cast<unsigned int>(woodTexs.size());
    for(unsigned int i = 0; i < woodTexNum; i++, srvIdx++)
        _device->CreateCSUView(_csuHeap.get(), srvIdx, _woodTexBuffs[i].Get(), View::SRV);

    // 将棋オブジェクト用SRV作成
    unsigned int pieceTextureNum = 8;
    auto designTextures = textures->GetDesignTextures();
    auto designTextureNum = static_cast<unsigned int>(designTextures.size());
    unsigned int shogiObjTextureNum = pieceTextureNum + designTextureNum;
    for (unsigned int i = 0; i < shogiObjTextureNum; i++, srvIdx++)
        _device->CreateCSUView(_csuHeap.get(), srvIdx, _shogiObjTexBuffs[i].Get(), View::SRV);

    // エフェクトテクスチャ用SRV作成
    auto effectTexs = textures->GetEffectTextures();
    auto effectTexNum = static_cast<unsigned int>(effectTexs.size());
    for(unsigned int i = 0; i < effectTexNum; i++, srvIdx++)
        _device->CreateCSUView(_csuHeap.get(), srvIdx, _effectTexBuffs[i].Get(), View::SRV);


    // レンダーによるテクスチャ作成用RTV作成
    for(UINT i = 0; i < pieceTextureNum; i++)
        _device->CreateView(_texRTVHeap.get(), i, _shogiObjTexBuffs[i].Get(), View::RTV);

}

// シェーダー系作成
ComPtr<ID3DBlob> DX12::CreateShader(
    std::wstring fileName,
    std::string funcName,
    std::string shaderType)
{
    ComPtr<ID3DBlob> comPtr;
   
    std::wstring path = L"shader/";

    HRESULT result;
    result = D3DCompileFromFile(
        (path + fileName).c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        funcName.c_str(),
        shaderType.c_str(),
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        comPtr.ReleaseAndGetAddressOf(),
        nullptr);
    assert(SUCCEEDED(result));

    return comPtr;
}



// 描画領域系作成
void DX12::CreateDrawArea()
{
    // ゲームウインドウ取得
    auto gameWindow = Application::GetInstance().GetGameWindow();

    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    // メイン
    // ビューポート
    _mainViewport->TopLeftX = 0.0f; // 左上横位置
    _mainViewport->TopLeftY = 0.0f; // 左上縦位置
    _mainViewport->Width    = static_cast<float>(windowWidth);  // 横
    _mainViewport->Height   = static_cast<float>(windowHeight); // 縦
    _mainViewport->MaxDepth = 1.0f; // 深度最大値
    _mainViewport->MinDepth = 0.0f; // 深度最小値
    // シザー矩形
    _mainScissorRect->left   = 0;            // 左
    _mainScissorRect->right  = windowWidth;  // 右
    _mainScissorRect->top    = 0;            // 上
    _mainScissorRect->bottom = windowHeight; // 下

    // マップ
    // ビューポート
    unsigned int offset = 10;
    auto length = windowHeight / 2;
    auto topY   = windowHeight - length;
    _mapViewport->TopLeftX = static_cast<float>(offset);        // 左上横位置
    _mapViewport->TopLeftY = static_cast<float>(topY - offset); // 左上縦位置
    _mapViewport->Width    = static_cast<float>(length);        // 横
    _mapViewport->Height   = static_cast<float>(length);        // 縦
    _mapViewport->MaxDepth = 1.0f; // 深度最大値
    _mapViewport->MinDepth = 0.0f; // 深度最小値
    // シザー矩形
    _mapScissorRect->left   = 26;                    // 左
    _mapScissorRect->right  = length - 10;           // 右
    _mapScissorRect->top    = topY - offset;         // 上
    _mapScissorRect->bottom = windowHeight - offset; // 下


}


// Direct2D系作成
void DX12::CreateD2D()
{   
    auto gameWindow = Application::GetInstance().GetGameWindow();


    // Direct3D11系作成
    auto device11AndDeviceContext = CreateDX11Device();
    _device11.swap(device11AndDeviceContext.device11);
    _deviceContext = device11AndDeviceContext.deviceContext;

    // Direct2Dファクトリー系作成
    _direct2DFactory = CreateDirect2DFactory(); // Direct2Dファクトリー作成

    auto dxgiDevice = _device11->GetDXGIDevice();                                // DXGIデバイス取得
    _direct2DDevice  = _direct2DFactory->CreateDirect2DDevice(dxgiDevice.Get()); // Direct2Dデバイス作成
    _direct2DFactory.reset(); // Direct2Dファクトリー解放
    
    _direct2DDeviceContext = _direct2DDevice->CreateDirect2DDeviceContext(); // Direct2Dデバイスコンテキスト作成
    _direct2DDevice.reset(); // Direct2Dデバイス解放
    

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    _swapChain->GetDesc(&swapChainDesc);
    unsigned int backBuffNum;
    backBuffNum = swapChainDesc.BufferCount;

    _wrappedBackBuffs.resize(backBuffNum);
    _d2dRenderTargets.resize(backBuffNum);
    for (UINT i = 0; i < backBuffNum; i++)
    {
        // ラップされたバックバッファ作成
        _wrappedBackBuffs[i] = _device11->CreateWrappedBackBuff(_backBuffs[i].Get());
    }
    
    for (UINT i = 0; i < backBuffNum; i++)
    {
        // DXGIサーフェイス作成
        Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
        _wrappedBackBuffs[i].As(&dxgiSurface);
        // Direct2Dレンダーターゲット作成
        _d2dRenderTargets[i] = _direct2DDeviceContext->CreateD2DRenderTarget(dxgiSurface.Get());
    }

    // ラップされた駒テクスチャバッファ作成
    unsigned int pieceBuffNum = 8;
    for (UINT i = 0; i < pieceBuffNum; i++)
        _wrappedPieceTexBuffs.push_back(_device11->CreateWrappedTexBuff(_shogiObjTexBuffs[i].Get()));

    // Direct2Dレンダーターゲット作成
    _d2dPieceTexRenderTargets.resize(pieceBuffNum);
    for (UINT i = 0; i < pieceBuffNum; i++)
    {
        // DXGIサーフェイス作成
        Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
        _wrappedPieceTexBuffs[i].As(&dxgiSurface);

        _d2dPieceTexRenderTargets[i] = _direct2DDeviceContext->CreateD2DRenderTarget(dxgiSurface.Get());
    }
        
    // テキストフォーマット作成
    _directWriteFactory = std::make_unique<DirectWriteFactory>();
    _pieceTextFormat = _directWriteFactory->CreatePieceTextFormat(); // 駒のテキストフォーマット作成
    _normalTextFormat = _directWriteFactory->CreateUITextFormat(); // 通常テキストフォーマット作成
    _titleTextFormat      = _directWriteFactory->CreateTitleTextFormat(DWRITE_FONT_WEIGHT_LIGHT); // タイトルテキストフォーマット作成
    _titleFrameTextFormat = _directWriteFactory->CreateTitleTextFormat(DWRITE_FONT_WEIGHT_BOLD);   // タイトル枠テキストフォーマット作成
    
    // ブラシ作成
    _blackBrush                 = _direct2DDeviceContext->CreateBrush(D2D1::ColorF(D2D1::ColorF::Black)); // 黒色ブラシ作成
    _redBrush                   = _direct2DDeviceContext->CreateBrush(D2D1::ColorF(D2D1::ColorF::Red)); // 赤色ブラシ作成
    _yellowBrush                = _direct2DDeviceContext->CreateBrush(D2D1::ColorF(D2D1::ColorF::Yellow)); // 黄色ブラシ作成
    _buttonUIBackBrush          = _direct2DDeviceContext->CreateBrush(D2D1::ColorF(D2D1::ColorF::LightYellow, 0.9f)); // UIブラシ作成
    _buttonUIBackBrushNotActive = _direct2DDeviceContext->CreateBrush(D2D1::ColorF(D2D1::ColorF::Gray, 0.9f)); // UI非活性ブラシ作成
}

// DirectX11系デバイス作成
Device11AndDeviceContext DX12::CreateDX11Device()
{
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    // デバッグモードならデバッグ出力
    flags += D3D11_CREATE_DEVICE_DEBUG;
#endif

    ComPtr<ID3D11Device> device11ComPtr;
    ComPtr<ID3D11DeviceContext> deviceContextComPtr;

    HRESULT result;
    result =  D3D11On12CreateDevice(
        _device->GetDevice(),
        flags,
        nullptr, // 3D12の機能レベル使用
        0,       // 機能レベル配列サイズ(nullptrのため0）
        reinterpret_cast<IUnknown**>(_cmdQueue.GetAddressOf()),
        1, // キューの個数 1
        0, // ノードマスク
        device11ComPtr.     ReleaseAndGetAddressOf(),
        deviceContextComPtr.ReleaseAndGetAddressOf(),
        nullptr); // 機能レベル返却先 nullptr
    assert(SUCCEEDED(result));

    ComPtr<ID3D11On12Device> device11On12ComPtr;
    result = device11ComPtr.As(&device11On12ComPtr);
    assert(SUCCEEDED(result));

    Device11AndDeviceContext device11AndDeviceContext;

    device11AndDeviceContext.device11      = std::make_unique<Device11>(device11On12ComPtr);
    device11AndDeviceContext.deviceContext = deviceContextComPtr;

    return device11AndDeviceContext;
}

// Direct2Dファクトリー作成
std::unique_ptr<Direct2DFactory> DX12::CreateDirect2DFactory()
{
    ComPtr<ID2D1Factory3> comPtr;

    HRESULT result;

    result = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        __uuidof(ID2D1Factory3),
        nullptr,
        reinterpret_cast<void**>(comPtr.ReleaseAndGetAddressOf()));

    assert(SUCCEEDED(result));

    return std::make_unique<Direct2DFactory>(comPtr);
}




// バッファに書き込み
void DX12::WriteToBuff()
{
    auto& app    = Application::GetInstance();

    auto gameObjects = app.GetGameObjects();


    auto boardVertIndices = gameObjects->GetBoardVertIndices();
    auto pieceVertIndices = gameObjects->GetPieceVertIndices();

    auto mainCamera = app.GetMainCamera();
    auto mapCamera  = app.GetMapCamera();

    auto address = _vertBuff->GetGPUVirtualAddress();


    // 頂点集合の書き込み位置をセット
    auto allGameObjects = gameObjects->GetAllGameObjects();
    unsigned int idx = 0;
    for (auto& gameObject : allGameObjects)
    {
        auto vertices = gameObject->GetVertices();
        vertices->SetStartDataIdx(idx);
        idx += static_cast<unsigned int>(vertices->GetDatas().size());
    }

    // 頂点集合をバッファに書き込み
    for (auto& gameObject : allGameObjects)
    {
        auto vertices = gameObject->GetVertices();
        vertices->WriteToBuff(_vertBuff.Get());
    }

    // インデックス集合の書き込み位置をセット
    idx = 0;
    boardVertIndices->SetStartDataIdx(idx);
    idx += static_cast<unsigned int>(boardVertIndices->GetDatas().size());
    pieceVertIndices->SetStartDataIdx(idx);
    boardVertIndices->WriteToBuff(_idxBuff.Get()); // 将棋盤インデックス集合をバッファに書き込み
    pieceVertIndices->WriteToBuff(_idxBuff.Get()); // 駒のインデックス集合をバッファに書き込み

    // 定数データの書き込み位置をセット（後に書き込む）
    auto board  = gameObjects->GetBoard();
    auto pieces = gameObjects->GetPieces();
    idx = 0;
    for (auto& gameObject : allGameObjects)
    {
        auto worldMat = gameObject->GetWorldMat();
        worldMat->SetStartDataIdx(idx);

        idx++;
    }
    mainCamera->SetStartDataIdx(idx);
    mapCamera ->SetStartDataIdx(idx);

    // 以下、テクスチャを書き込む
    auto textures      = app.GetTextures();

    // 木材テクスチャをバッファに書き込み
    auto woodTexs      = textures->GetWoodTextures();
    auto woodTexNum = static_cast<unsigned int>(woodTexs.size());
    for(unsigned int i = 0; i < woodTexNum; i++)
        woodTexs[i]->WriteToBuff(_woodTexBuffs[i].Get()); 

    // オブジェクトごとのテクスチャをバッファに書き込み
    auto designTexs = textures->GetDesignTextures();
    auto designTexNum = static_cast<unsigned int>(designTexs.size());
    for(unsigned int i = 0; i < designTexNum; i++)
        designTexs[i]->WriteToBuff(_shogiObjTexBuffs[static_cast<unsigned int>(GameObjType::BOARD_55) + i].Get()); 

    // エフェクトのテクスチャをバッファに書き込み
    auto effectTexs = textures->GetEffectTextures();
    auto effectTexNum = static_cast<unsigned int>(effectTexs.size());
    for(unsigned int i = 0; i < effectTexNum; i++)
        effectTexs[i]->WriteToBuff(_effectTexBuffs[i].Get()); 

}

// レンダーテクスチャ作成
void DX12::CreateRenderTex()
{
    // 駒テクスチャ作成
    CreatePieceTex(GameObjType::KING,   L"王",   L"");
    CreatePieceTex(GameObjType::ROOK,   L"飛車", L"龍王");
    CreatePieceTex(GameObjType::BISHOP, L"角行", L"龍馬");
    CreatePieceTex(GameObjType::GOLD,   L"金将", L"");
    CreatePieceTex(GameObjType::SILVER, L"銀将", L"成銀");
    CreatePieceTex(GameObjType::KNIGHT, L"桂馬", L"成桂");
    CreatePieceTex(GameObjType::LANCE,  L"香車", L"成香");
    CreatePieceTex(GameObjType::PAWN,   L"歩",   L"と");

    // リソース開放
    for (auto& wrappedPieceTexBuff : _wrappedPieceTexBuffs) 
        wrappedPieceTexBuff.Reset(); // ラップされたレンダーテクスチャバッファ
    _texRTVHeap.reset(); // テクスチャ用RTVヒープ
}




// 駒テクスチャ作成
void DX12::CreatePieceTex(
    GameObjType shogiObjType,
    std::wstring frontText,
    std::wstring backText)
{
    InitRenderTex(shogiObjType); // テクスチャへのレンダリング初期処理

    unsigned int idx = static_cast<unsigned int>(shogiObjType);
    
    auto wrappedRenderTexBuffAddress = _wrappedPieceTexBuffs[idx].GetAddressOf();         // ラップされたバッファ
    auto d2dRenderTarget = _d2dPieceTexRenderTargets[idx].Get(); // レンダーターゲット

    StartD2D(wrappedRenderTexBuffAddress, d2dRenderTarget); // Direct2D開始
    
    auto size = 256.0f / 2.0f;
    D2D1_RECT_F rect = {0, 5, size, size};
    _direct2DDeviceContext->DrawTextW( // 黒色で駒表面文字を描画
        frontText,
        rect,
        _pieceTextFormat.Get(),
        _blackBrush.Get());

    rect.left += size;
    rect.right += size;
    _direct2DDeviceContext->DrawTextW( // 赤色で駒裏面文字を描画
        backText,
        rect,
        _pieceTextFormat.Get(),
        _redBrush.Get());

    EndD2D(wrappedRenderTexBuffAddress); // Direct2D終了

    ExitRenderTex(shogiObjType); // レンダリング終了処理
}

// テクスチャへのレンダリング初期処理
void DX12::InitRenderTex(GameObjType shogiObjType)
{
    unsigned int idx = static_cast<unsigned int>(shogiObjType);
    // テクスチャのリソースバリアをレンダーターゲットに変更
    auto renderTexBuff = _shogiObjTexBuffs[idx].Get();
    auto resourceBarrier = _rb->GetRBTexToRenderTarget(renderTexBuff);
    _cmdList->ResourceBarrier(1, &resourceBarrier);

    // レンダーターゲットに設定
    auto rtvHandle = _texRTVHeap->GetDescHandle(idx);
    _cmdList->OMSetRenderTargets(1, &rtvHandle, true, nullptr);

    // レンダーターゲットクリア
    float clearRTVColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    _cmdList->ClearRenderTargetView(rtvHandle, clearRTVColor, 0, nullptr);

    ExeCmd(); // コマンド実行
}

// Direct2D開始
void DX12::StartD2D(ID3D11Resource** wrappedBuff, ID2D1Bitmap1* d2dRenderTarget)
{
    _device11->AcquireWrappedBuff(wrappedBuff);
    _direct2DDeviceContext->SetRenderTarget(d2dRenderTarget);
    _direct2DDeviceContext->BeginDraw();
    _direct2DDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
}

// Direct2D終了
void DX12::EndD2D(ID3D11Resource** wrappedBuff)
{
    _direct2DDeviceContext->EndDraw();
    _device11->ReleaseWrappedBuff(wrappedBuff);
    _deviceContext->Flush(); // Direct2D描画
}

// テクスチャへのレンダリング終了処理
void DX12::ExitRenderTex(GameObjType shogiObjType)
{
    unsigned int idx = static_cast<unsigned int>(shogiObjType);
    // テクスチャのリソースバリアをテクスチャに戻す
    auto renderTexBuff = _shogiObjTexBuffs[idx].Get();
    auto resourceBarrier = _rb->GetRBRenderTargetToTex(renderTexBuff);
     _cmdList->ResourceBarrier(1, &resourceBarrier);

    ExeCmd(); // コマンド実行
}


///////////////////////////////////////////////////////////////////////


// コマンド実行
void DX12::ExeDX12()
{
    
    _currentBackBuffIdx = _swapChain->GetCurrentBackBufferIndex(); // バックバッファインデックス取得
    
    InitRenderTarget(); // レンダーターゲット初期処理
    ExeD3D(); // Direct3D処理実行
    ExeD2D(); // Direct2D処理実行
    PrepareRenderTargetToFlip(); // 画面フリップ準備処理
    _swapChain->Present(1, 0); // 画面フリップ
}

// レンダーターゲット初期処理
void DX12::InitRenderTarget()
{
    // バックバッファリソースをレンダーターゲットに変更
    auto resourceBarrier = _rb->GetRBToRenderTarget(_backBuffs[_currentBackBuffIdx].Get());
    _cmdList->ResourceBarrier(1, &resourceBarrier);

    // バックバッファをレンダーターゲットに設定
    auto rtvHandle = _rtvHeap->GetDescHandle(_currentBackBuffIdx);
    auto dsvHandle = _dsvHeap->GetDescHandle(0);
    _cmdList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);

    // クリア処理
    float clearRTVColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    _cmdList->ClearRenderTargetView(rtvHandle, clearRTVColor, 0, nullptr);
    _cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}




// Direct3D処理実行
void DX12::ExeD3D()
{
    auto& app    = Application::GetInstance();
    auto  gameObjects = app.GetGameObjects();
    auto  board  = gameObjects->GetBoard();

    auto mainCamera = app.GetMainCamera();
    auto mapCamera = app.GetMapCamera();

    Set3DCmd(); // 3Dコマンドセット

    // ビューポートセット
    D3D12_VIEWPORT viewports[] = {*_mainViewport.get()};
    _cmdList->RSSetViewports(1, viewports);

    // シザー矩形セット
    D3D12_RECT scissorRects[] = {*_mainScissorRect.get()};
    _cmdList->RSSetScissorRects(1, scissorRects);

    SetCommandDrawGameObj(); // ゲームオブジェクト描画コマンドセット

    // 駒の頂点集合をバッファに書き込み
    auto pieces = gameObjects->GetPieces();
    for (auto& piece : pieces)
    {
        auto vertices = piece->GetVertices();
        vertices->WriteToBuff(_vertBuff.Get());
    }
    // 定数バッファに書き込み
    auto allGameObjects = gameObjects->GetAllGameObjects();
    for (auto& gameObject : allGameObjects)
    {
        auto worldMat = gameObject->GetWorldMat();
        worldMat->WriteToBuff(_constBuff.Get());
    }
    mainCamera->WriteToBuff(_constBuff.Get()); // メインカメラ書き込み

    // 将棋盤のエフェクトテクスチャをバッファに書き込み
    // エフェクトのテクスチャをバッファに書き込み
    auto effectTexs = app.GetTextures()->GetEffectTextures();
    auto effectTexNum = static_cast<unsigned int>(effectTexs.size());
    for(unsigned int i = 0; i < effectTexNum; i++)
        effectTexs[i]->WriteToBuff(_effectTexBuffs[i].Get()); 
    
    ExeCmd(); // コマンド実行


    // マップ描画フラグがオンならマップ描画
    if (Application::GetInstance().IsDrawMap())
    {
        // バックバッファをレンダーターゲットに設定
        auto rtvHandle = _rtvHeap->GetDescHandle(_currentBackBuffIdx);
        auto dsvHandle = _dsvHeap->GetDescHandle(0);
        _cmdList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);

        // クリア処理
        _cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

        Set3DCmd(); // 3Dコマンドセット

        // ビューポートセット
        viewports[0] = {*_mapViewport.get()};
        _cmdList->RSSetViewports(1, viewports);

        // シザー矩形セット
        scissorRects[0] = {*_mapScissorRect.get()};
        _cmdList->RSSetScissorRects(1, scissorRects);

        SetCommandDrawGameObj(); // ゲームオブジェクト描画コマンドセット
        
        // カメラをマップカメラに変更
        mapCamera->WriteToBuff(_constBuff.Get());

        ExeCmd(); // コマンド実行
    }
}

// ゲームオブジェクト描画コマンドセット
void DX12::SetCommandDrawGameObj()
{
    auto gameObjects = Application::GetInstance().GetGameObjects();
    auto cubeVertIndices  = gameObjects->GetBoardVertIndices();
    auto pieceVertIndices = gameObjects->GetPieceVertIndices();

    // 将棋盤描画コマンドセット
    auto board  = gameObjects->GetBoard();
    auto idxBuffView = GetIdxBuffView(cubeVertIndices);
    _cmdList->IASetIndexBuffer(&idxBuffView);
    auto vertBuffView = GetVertBuffView(board->GetVertices());
    _cmdList->IASetVertexBuffers(0, 1, &vertBuffView);
    _cmdList->DrawIndexedInstanced(static_cast<unsigned int>(cubeVertIndices->GetDatas().size()), 1, 0, 0, 0);

    // 駒置き台描画コマンドセット
    auto sideBoards = gameObjects->GetSideBoards();
    _cmdList->IASetIndexBuffer(&idxBuffView);
    for (auto& sideBoard : sideBoards)
    {
        auto vertBuffView = GetVertBuffView(sideBoard->GetVertices());
        _cmdList->IASetVertexBuffers(0, 1, &vertBuffView);
        _cmdList->DrawIndexedInstanced(static_cast<unsigned int>(cubeVertIndices->GetDatas().size()), 1, 0, 0, 0);
    }

    // 駒描画コマンドセット
    auto pieces = gameObjects->GetPieces();
    idxBuffView = GetIdxBuffView(pieceVertIndices);
    _cmdList->IASetIndexBuffer(&idxBuffView);
    for (auto& piece : pieces)
    { 
        auto vertBuffView = GetVertBuffView(piece->GetVertices());
        _cmdList->IASetVertexBuffers(0, 1, &vertBuffView);
        _cmdList->DrawIndexedInstanced(static_cast<unsigned int>(pieceVertIndices->GetDatas().size()), 1, 0, 0, 0);
    }
}

// 3Dコマンドセット
void DX12::Set3DCmd()
{
    // パイプラインセット
    _cmdList->SetPipelineState(_pipeline.Get());

    // ルートシグネチャセット
    _cmdList->SetGraphicsRootSignature(_rootSignature.Get());

    // CSUヒープセット
    ID3D12DescriptorHeap* csuHeaps[] = {_csuHeap->GetHeap()};
    auto csuHeapNum = sizeof(csuHeaps) / sizeof(ID3D12DescriptorHeap*);
    _cmdList->SetDescriptorHeaps(1, csuHeaps); 

    // ルートパラメータとディスクリプタ関連付け
    _cmdList->SetGraphicsRootDescriptorTable(0, _csuHeap->GetGPUCBVHandle(0)); // CBV
    _cmdList->SetGraphicsRootDescriptorTable(1, _csuHeap->GetGPUSRVHandle(0)); // SRV

    // トポロジーセット
    _cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertBuffView(NaturalBufferedData<Vert>* vertices)
{
    D3D12_VERTEX_BUFFER_VIEW view;

    auto buffAddress = _vertBuff->GetGPUVirtualAddress();
    buffAddress += sizeof(Vert) * vertices->GetStartDataIdx();

    view.BufferLocation =  // 頂点バッファのスタート位置
        buffAddress;
    view.StrideInBytes =   // 頂点1つ分のサイズ
        sizeof(Vert);
    view.SizeInBytes = // 頂点全体のサイズ
        sizeof(Vert) * static_cast<unsigned int>(vertices->GetDatas().size());

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIdxBuffView(NaturalBufferedData<unsigned short>* vertIndices)
{
    D3D12_INDEX_BUFFER_VIEW view;

    auto startBuffAddress = _idxBuff->GetGPUVirtualAddress();
    startBuffAddress += sizeof(unsigned short) * vertIndices->GetStartDataIdx();

    view.BufferLocation = // インデックスバッファのスタート位置
        startBuffAddress;
    view.Format =         // フォーマット unsigned short
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =    // インデックス全体のサイズ
        sizeof(unsigned short) * static_cast<unsigned int>(vertIndices->GetDatas().size());

    return view;
}


// コマンド実行
void DX12::ExeCmd()
{
    _cmdList->Close(); // コマンドクローズ

    // コマンド実行
    ID3D12CommandList* commandLists[] = {_cmdList.Get()}; // リストに格納
    _cmdQueue->ExecuteCommandLists(1, commandLists); // コマンドキュー実行

    WaitProcessWithFence(); // フェンスによる同期処理
    _cmdAllocator->Reset();               // コマンドアロケータリセット
    _cmdList->Reset(_cmdAllocator.Get(), nullptr); // コマンドリストリセット
}



// Direct2D処理実行
void DX12::ExeD2D()
{
    auto wrappedBackBuffAddress = _wrappedBackBuffs[_currentBackBuffIdx].GetAddressOf();
    auto d2dRenderTarget = _d2dRenderTargets[_currentBackBuffIdx].Get();
    auto frameUIs = Application::GetInstance().GetFrameUIs();
    auto textUIs = Application::GetInstance().GetTextUIs();
    auto buttons = Application::GetInstance().GetButtons();
    StartD2D(wrappedBackBuffAddress, d2dRenderTarget); // Direct2D開始

    // ボタン選択処理
    for (auto& button : buttons) button->ExeSelectedStateProcess();

    // テキスト枠UI描画

    for (auto& frameUI : frameUIs)
    {
        ID2D1SolidColorBrush* backBrush;
        if (frameUI->GetIsActive())
        {
            backBrush = _buttonUIBackBrush.Get();
        }
        else
        {
            backBrush = _buttonUIBackBrushNotActive.Get();
        }
        _direct2DDeviceContext->DrawRectangle(
            frameUI->GetRect(),
            backBrush,
            _blackBrush.Get());
    }

    // テキストUI描画
    for (auto& textUI : textUIs)
    {
        _direct2DDeviceContext->DrawText2D(textUI->GetText2D());
    }
        
    EndD2D(wrappedBackBuffAddress); // Direct2D終了
}




// レンダーターゲットのフリップ準備
void DX12::PrepareRenderTargetToFlip()
{
    // バックバッファを表示画面に設定
    auto resourceBarrier = _rb->GetRBToPresent(_backBuffs[_currentBackBuffIdx].Get());
    _cmdList->ResourceBarrier(1, &resourceBarrier);

    ExeCmd(); // コマンド実行
}



// フェンスによる同期制御
void DX12::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _fenceVal++;
    _cmdQueue->Signal(_fence.Get(), _fenceVal);
    
    // フェンス値が更新されるまで待機
    while (_fence->GetCompletedValue() != _fenceVal)
    {
        HANDLE event = nullptr;
        _fence->SetEventOnCompletion(_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}


IDWriteTextFormat* DX12::GetNormalTextFormat(){return _normalTextFormat.Get();} // 通常のテキストフォーマットを返す
IDWriteTextFormat* DX12::GetTitleTextFormat     (){return _titleTextFormat.Get();}      // タイトルテキストフォーマットを返す
IDWriteTextFormat* DX12::GetTitleFrameTextFormat(){return _titleFrameTextFormat.Get();} // タイトル枠テキストフォーマットを返す

ID2D1SolidColorBrush* DX12::GetBlackBrush() {return _blackBrush .Get();} // 黒色ブラシを返す
ID2D1SolidColorBrush* DX12::GetRedBrush()   {return _redBrush   .Get();} // 赤色ブラシを返す
ID2D1SolidColorBrush* DX12::GetYellowBrush(){return _yellowBrush.Get();} // 黄色ブラシを返す


//// 描画設定更新
//HRESULT Draw::UpdateDrawConf(
//    ID3D12Device* device,
//    UINT width, 
//    UINT height,
//    UINT buffNum)
//{
//    WaitProcessWithFence(); // GPUが処理中であれば待つ
//    
//    _rtvHeap->ClearRTV(); // RTV破棄
//    if(FAILED(_swapChain->UpdateSwapChain( // スワップチェーン更新
//        width, height)))
//    {
//        assert(false); return E_FAIL;
//    }
//    if (FAILED(_rtvHeap->CreateRTV( // RTV再作成
//        device, _swapChain->GetSwapChain(), buffNum)))
//    {
//        assert(false); return E_FAIL;
//    }
//
//    return S_OK;
//}






//// ウインドウサイズ変更処理
//void DX12::ProcessChangeWindowSize(UINT width, UINT height)
//{   
//    // スワップチェーン更新
//    _draw->UpdateDrawConf(
//        _device->GetDevice(),
//        width, 
//        height,
//        _rtBuffNum);
//}

DX12::DX12() {
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _mainViewport    = std::make_unique<D3D12_VIEWPORT>();
    _mainScissorRect = std::make_unique<D3D12_RECT>();
    _mapViewport     = std::make_unique<D3D12_VIEWPORT>();
    _mapScissorRect  = std::make_unique<D3D12_RECT>();


    _rb = std::make_unique<ResourceBarrier>();
}