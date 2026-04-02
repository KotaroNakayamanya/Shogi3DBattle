#include"DX12.h"

#include"Application.h"
#include<algorithm>
#include<cassert>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    // デバッグ有効化
    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;

        D3D12GetDebugInterface(
            IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期処理
bool DX12::InitDX12(GameWindow* gameWindow)
{
    if(FAILED(CreateFactory())) goto failed; // ファクトリー系作成
    if(FAILED(CreateCommand())) goto failed; // コマンド系作成
    if(FAILED(_dxgiFactory->CreateSwapChain(_swapChain.get(), _cmdQueue.get(), gameWindow))) goto failed; // スワップチェーン作成
    if(FAILED(_device->CreateFence(_fence.get()))) goto failed; // フェンス作成
    
    if(FAILED(CreateBuff())) goto failed; // バッファ系作成
    if(FAILED(CreateHeap())) goto failed; // ヒープ作成
    CreateView(); // ビュー作成
    
    if (FAILED(_device->CreateRootSignature(_rootSignature.get(), _csuHeap.get()))) goto failed; // ルートシグネチャオブジェクト作成
    _device->CreateInputLayout(_inputLayout.get()); // 頂点バッファ入力レイアウト作成
    if(FAILED(CreateShader())) goto failed; // シェーダー系作成

    // パイプラインオブジェクト作成
    if (FAILED(_device->CreatePipeline(
        _pipeline.get(),      // パイプライン
        _rootSignature.get(), // ルートシグネチャ
        _inputLayout.get(),   // 入力レイアウト
        _vShader.get(),       // 頂点シェーダ
        _pShader.get())))     // ピクセルシェーダ
        goto failed;

    
    CreateDrawArea(); // 描画領域系作成
    
    if(FAILED(CreateD2D())) goto failed; // DirectX11系作成 

    if(FAILED(WriteToBuff())) goto failed; // バッファに書き込み

    CreateRenderTex(); // レンダーテクスチャ作成


    
    return true;

failed:
    assert(false);
    return false;
}




// ファクトリー系作成
HRESULT DX12::CreateFactory()
{
    // DXGIファクトリー作成
    if(FAILED(CreateDXGIFactory())) goto failed;
    // アダプター作成
    if (FAILED(_dxgiFactory->CreateAdapter(_adapter.get()))) goto failed;
    // デバイス作成
    if (FAILED(_dxgiFactory->CreateDevice(_device.get(), _adapter.get()))) goto failed;
    
    _adapter.reset(); // アダプター破棄
    
    return S_OK;

failed:
    return E_FAIL;
}

// DXGIファクトリー作成
HRESULT DX12::CreateDXGIFactory()
{
    HRESULT result;

    ComPtr<IDXGIFactory6> dxgiFactoryCom
    ;

    // デバッグモードのときは詳細を表示させるファクトリーを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(dxgiFactoryCom.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(dxgiFactoryCom.ReleaseAndGetAddressOf()));
#endif
    
    if(FAILED(result)) return result;

    _dxgiFactory->SetDXGIFactory(dxgiFactoryCom);

    return S_OK;
}




// コマンド系作成
HRESULT DX12::CreateCommand()
{
    // コマンドアロケータ作成
    if (FAILED(_device->CreateCmdAllocator(_cmdAllocator.get()))) goto failed;
    // コマンドリスト作成
    if (FAILED(_device->CreateCmdList(_cmdList.get(), _cmdAllocator.get()))) goto failed;
    // コマンドキュー作成
    if (FAILED(_device->CreateCmdQueue(_cmdQueue.get()))) goto failed;

    return S_OK;

failed:
    return E_FAIL;
}




// DirectWriteファクトリー作成
HRESULT DX12::CreateDWriteFactory()
{
    return DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(_dWriteFactory->_dWriteFactory.ReleaseAndGetAddressOf()));
}




// バッファ系作成
HRESULT DX12::CreateBuff()
{
    auto& app = Application::GetInstance();
    
    auto  woodTex = app.GetWoodTex();
    
    //auto& boardLineTexs = app.GetBoardLineTexs();
    //auto  boardLineTex = app.GetBoardLineTex();
    
    auto shogiObjects   = app.GetShogiObjects();
    auto allVertIndices = app.GetAllVertIndices();

    std::vector<ShogiObj::ShogiObjType> boardType =
    {
        ShogiObj::BOARD_55,
        ShogiObj::BOARD_99
    };


    // バックバッファ作成
    _backBuffs.resize(_swapChain->GetBackBuffNum());
    for (UINT i = 0; i < _backBuffs.size(); i++)
    {
        _backBuffs[i] = std::make_unique<Buff>();
        if (FAILED(_swapChain->CreateBackBuff(_backBuffs[i].get(), i))) goto failed;
    }

    // デプスステンシルバッファ作成
    D3D12_RESOURCE_DESC backBuffDesc;
    backBuffDesc = _backBuffs[0]->GetResourceDesc();
    UINT widthSize, heightSize;
    widthSize  = backBuffDesc.Width;
    heightSize = backBuffDesc.Height;
    if (FAILED(_device->CreateBuff(_dsBuff.get(), widthSize, heightSize, Buff::DEPTH_STENCIL))) goto failed;

    // コンスタントバッファ作成
    UINT shogiObjNum, viewProjNum, totalMatNum;
    shogiObjNum = shogiObjects.size();
    viewProjNum = 1;
    totalMatNum = shogiObjNum + viewProjNum;
    widthSize  = (sizeof(DirectX::XMMATRIX)*totalMatNum + 0xff) & ~0xff; // 256アラインメント
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_constBuff.get(), widthSize, heightSize, Buff::CONSTANT))) goto failed;

    // 頂点バッファ作成
    widthSize = 0;
    //for(auto& shogiObject : shogiObjects) {widthSize += shogiObject->GetVertices()->GetVerticesByteSize();}
    for(auto& shogiObj : shogiObjects) widthSize += sizeof(ShogiObj::Vert) * shogiObj->GetVertices().size();
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_vertBuff.get(), widthSize, heightSize, Buff::VERTEX))) goto failed;

    // 頂点インデックスバッファ作成
    widthSize = 0;
    for(auto& vertIndices : allVertIndices) {widthSize += vertIndices->GetVertIndicesByteSize();}
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_idxBuff.get(), widthSize, heightSize, Buff::INDEX))) goto failed;

    // 木材テクスチャバッファ作成
    widthSize  = woodTex->GetWidth();
    heightSize = woodTex->GetHeight();
    if (FAILED(_device->CreateBuff(_woodTexBuff.get(), widthSize, heightSize, Buff::TEXTURE))) goto failed;

    // 将棋オブジェクト種類ごとのテクスチャバッファ作成
    UINT shogiObjTexNum;
    shogiObjTexNum = ShogiObj::TYPE_NUM;
    _shogiObjTexBuffs.resize(shogiObjTexNum);
    for(auto& shogiObjTexBuff : _shogiObjTexBuffs) shogiObjTexBuff = std::make_unique<TexBuff>();
    widthSize = 256;
    widthSize = 256;
    for (UINT i = 0; i < shogiObjTexNum; i++)
    {
        // テクスチャのIDが将棋盤用のものかどうか調べる
        ShogiObj::ShogiObjType shogiObjType;
        shogiObjType = static_cast<ShogiObj::ShogiObjType>(i);
        auto it = std::find(boardType.begin(), boardType.end(), shogiObjType);

        Buff::BuffType buffType;
        if(it != boardType.end()) // 将棋盤用のテクスチャであれば前準備で用意したテクスチャを使用する
            buffType = Buff::TEXTURE;
        else                      // それ以外は駒のテクスチャで、レンダリングして作成する
            buffType = Buff::RENDER_TEX;

        if (FAILED(_device->CreateBuff(_shogiObjTexBuffs[i].get(), widthSize, heightSize, buffType))) goto failed;
    }

    return S_OK;

failed:
    return E_FAIL;
}

// ヒープ作成
HRESULT DX12::CreateHeap()
{
    // バックバッファRTVヒープ作成
    if (FAILED(_device->CreateHeap(_rtvHeap.get(), _swapChain->GetBackBuffNum(), Heap::RTV))) goto failed;

    // DSVヒープ作成
    if (FAILED(_device->CreateHeap(_dsvHeap.get(), 1, Heap::DSV))) goto failed;

    // CSUヒープ作成
    UINT pieceTexNum, boardTexNum;
    boardTexNum = 1;
    pieceTexNum = 8;
    UINT cbvNum, srvNum, uavNum;
    cbvNum = 1;
    srvNum = 1 + boardTexNum + pieceTexNum; // 木材テクスチャ1 将棋盤テクスチャ2　駒テクスチャ8
    uavNum = 0;
    if (FAILED(_device->CreateCSUHeap(_csuHeap.get(), cbvNum, srvNum, uavNum, Heap::CSU))) goto failed;

    // 駒ごとの文字テクスチャ作成用RTVヒープ
    if (FAILED(_device->CreateHeap(_texRTVHeap.get(), pieceTexNum, Heap::RTV))) goto failed;

    return S_OK;

failed:
    return E_FAIL;
}

// ビュー作成
void DX12::CreateView()
{
    auto& app = Application::GetInstance();
    auto shogiObjcts = app.GetShogiObjects();

    // バックバッファ用RTV作成
    for (UINT i = 0; i < _rtvHeap->GetDescNum(); i++)
    {
        _device->CreateView(_rtvHeap.get(), i, _backBuffs[i].get(), View::RTV);
    }

    // DSV作成
    for (UINT i = 0; i < _dsvHeap->GetDescNum(); i++)
    {
        _device->CreateView(_dsvHeap.get(), i, _dsBuff.get(), View::DSV);
    }

    // CBV作成
    for (UINT i = 0; i < _csuHeap->GetCBVNum(); i++)
    {
        _device->CreateCSUView(_csuHeap.get(), i, _constBuff.get(), View::CBV);
    }

    // 木材テクスチャ用SRV作成
    auto woodTexNum = 1;
    _device->CreateCSUView(_csuHeap.get(), 0, _woodTexBuff.get(), View::SRV);

    // 将棋オブジェクト用SRV作成
    auto shogiObjTexNum = 9;
    for (UINT i = 0; i < shogiObjTexNum; i++)
        _device->CreateCSUView(_csuHeap.get(), i + woodTexNum, _shogiObjTexBuffs[i].get(), View::SRV);

    // レンダーによるテクスチャ作成用RTV作成
    for(UINT i = 0; i < 8; i++)
        _device->CreateView(_texRTVHeap.get(), i, _shogiObjTexBuffs[i].get(), View::RTV);
}

// シェーダー系作成
HRESULT DX12::CreateShader()
{
    if (FAILED(_device->CreateVShader(_vShader.get()))) goto failed; // 頂点シェーダー作成
    if (FAILED(_device->CreatePShader(_pShader.get()))) goto failed; // ピクセルシェーダー作成

    return S_OK;

failed:
    return E_FAIL;
}

// 描画領域系作成
void DX12::CreateDrawArea()
{
    // ゲームウインドウ取得
    auto gameWindow = Application::GetInstance().GetGameWindow();

    // メイン
    // ビューポート
    _mainViewport->TopLeftX = 0; // 左上横位置
    _mainViewport->TopLeftY = 0; // 左上縦位置
    _mainViewport->Width    = gameWindow->GetWindowWidth();  // 横
    _mainViewport->Height   = gameWindow->GetWindowHeight(); // 縦
    _mainViewport->MaxDepth = 1.0f; // 深度最大値
    _mainViewport->MinDepth = 0.0f; // 深度最小値
    // シザー矩形
    _mainScissorRect->left   = 0;                             // 左
    _mainScissorRect->right  = gameWindow->GetWindowWidth();  // 右
    _mainScissorRect->top    = 0;                             // 上
    _mainScissorRect->bottom = gameWindow->GetWindowHeight(); // 下

    // マップ
    // ビューポート
    //auto width  = gameWindow->GetWindowWidth()  / 2;
    auto height = gameWindow->GetWindowHeight() / 2;
    //auto widthEdge = static_cast<int>(width - height) / 2;
    auto topY = gameWindow->GetWindowHeight() - height;
    int offset = 10;
    _mapViewport->TopLeftX = offset; // 左上横位置
    _mapViewport->TopLeftY = topY - offset; // 左上縦位置
    _mapViewport->Width    = height;  // 横
    _mapViewport->Height   = height; // 縦
    _mapViewport->MaxDepth = 1.0f; // 深度最大値
    _mapViewport->MinDepth = 0.0f; // 深度最小値
    // シザー矩形
    _mapScissorRect->left   = offset;                        // 左
    _mapScissorRect->right  = height;         // 右
    _mapScissorRect->top    = topY - offset;                 // 上
    _mapScissorRect->bottom = gameWindow->GetWindowHeight(); // 下


}


// Direct2D系作成
HRESULT DX12::CreateD2D()
{   
    // Direct3D11系作成
    if (FAILED(_device->CreateD3D11(_device11.get(), _deviceContext.get(), _cmdQueue.get()))) goto failed;
    // Direct2Dデバイスコンテキスト作成
    if (FAILED(_device11->CreateD2DDeviceContext(_d2dDeviceContext.get()))) goto failed;
    
    UINT backBuffNum; // バックバッファの数
    backBuffNum = _swapChain->GetBackBuffNum();
    _wrappedBackBuffs.resize(backBuffNum);
    _d2dRenderTargets.resize(backBuffNum);
    for (UINT i = 0; i < backBuffNum; i++)
    {
        // ラップされたバックバッファ作成
        _wrappedBackBuffs[i] = std::make_unique<WrappedBuff>();
        if (FAILED(_device11->CreateWrappedBackBuff(_wrappedBackBuffs[i].get(), _backBuffs[i].get()))) goto failed;
    }
    for (UINT i = 0; i < backBuffNum; i++)
    {
        // Direct2Dレンダーターゲット作成
        _d2dRenderTargets[i] = std::make_unique<D2DRenderTarget>();
        if (FAILED(_d2dDeviceContext->CreateD2DRenderTarget(_d2dRenderTargets[i].get(), _wrappedBackBuffs[i].get()))) goto failed;
    }

    // ラップされた駒テクスチャバッファ作成
    UINT boardBuffNum, pieceBuffNum;
    boardBuffNum = 2;
    pieceBuffNum = _shogiObjTexBuffs.size() - boardBuffNum;
    _wrappedPieceTexBuffs.resize(pieceBuffNum);
    for(auto& wrappedPieceTexBuff : _wrappedPieceTexBuffs) wrappedPieceTexBuff = std::make_unique<WrappedBuff>();
    for (UINT i = 0; i < pieceBuffNum; i++)
        if (FAILED(_device11->CreateWrappedTexBuff(_wrappedPieceTexBuffs[i].get(), _shogiObjTexBuffs[i].get()))) goto failed;

    // Direct2Dレンダーターゲット作成
    _d2dPieceTexRenderTargets.resize(pieceBuffNum);
    for(auto& d2dPieceTexRenderTarget : _d2dPieceTexRenderTargets) d2dPieceTexRenderTarget = std::make_unique<D2DRenderTarget>();
    for (UINT i = 0; i < pieceBuffNum; i++)
        if (FAILED(_d2dDeviceContext->CreateD2DRenderTarget(_d2dPieceTexRenderTargets[i].get(), _wrappedPieceTexBuffs[i].get()))) goto failed;

    // DirectWriteファクトリー作成
    if (FAILED(CreateDWriteFactory())) goto failed;
    
    // ブラシ作成
    if(FAILED(_d2dDeviceContext->CreateBrush(_blackBrush.get(), D2D1::ColorF(D2D1::ColorF::Black)))) goto failed; // 黒色ブラシ作成
    if(FAILED(_d2dDeviceContext->CreateBrush(_redBrush.get(), D2D1::ColorF(D2D1::ColorF::Red)))) goto failed; // 赤色ブラシ作成
    if(FAILED(_d2dDeviceContext->CreateBrush(_uiBrush.get(), D2D1::ColorF(D2D1::ColorF::LightYellow, 0.9f)))) goto failed; // UIブラシ作成


    // 駒のテキストフォーマット作成
    if(FAILED(_dWriteFactory->CreateTextFormat(_pieceTextFormat.get(), L"メイリオ"))) goto failed;
    // UIテキストフォーマット作成
    if(FAILED(_dWriteFactory->CreateUITextFormat(_uiTextFormat.get(), L"メイリオ", 50.0f))) goto failed;

    return S_OK;

failed:
    return E_FAIL;
}

// バッファに書き込み
HRESULT DX12::WriteToBuff()
{
    auto& app    = Application::GetInstance();
    auto  board  = app.GetBoard();
    auto& pieces = app.GetPieces();
    auto  woodTex = app.GetWoodTex();

    auto& boardLineTexs = app.GetBoardLineTexs();
    auto boardVertIndices = app.GetBoardVertIndices();
    auto pieceVertIndices = app.GetPieceVertIndices();

    UINT idx = 0;
    UINT address = _vertBuff->GetBuff()->GetGPUVirtualAddress();

    // 頂点集合の書き込み位置をセット
    board->SetStartVertIdxInBuff(idx);
    idx += board->GetVertices().size();
    for (auto& piece : pieces)
    {
        piece->SetStartVertIdxInBuff(idx);
        idx += piece->GetVertices().size();
    }

    // 将棋盤頂点集合をバッファに書き込み
    if(FAILED(_vertBuff->WriteToBuff<GameObj::Vert>(board->GetVertices(), board->GetStartVertIdxInBuff()))) goto failed;

    // 駒の頂点集合をバッファに書き込み
    for (auto& piece : pieces)
    {
        if(FAILED(_vertBuff->WriteToBuff<GameObj::Vert>(piece->GetVertices(), piece->GetStartVertIdxInBuff()))) goto failed;
    }



    //if (FAILED(_vertBuff->WriteToVertBuff(board, pieces))) goto failed; // 頂点バッファに書き込み

    if (FAILED(_idxBuff ->WriteToIdxBuff (boardVertIndices, pieceVertIndices)))  goto failed; // インデックスバッファに書き込み
    if(FAILED(_woodTexBuff->WriteToTexBuff(woodTex))) goto failed; // 木材テクスチャをバッファに書き込み

    if(FAILED(_shogiObjTexBuffs[ShogiObj::BOARD_55]->WriteToTexBuff(boardLineTexs[0].get()))) goto failed; // 5×5将棋盤黒線テクスチャをバッファに書き込み
    if(FAILED(_shogiObjTexBuffs[ShogiObj::BOARD_99]->WriteToTexBuff(boardLineTexs[1].get()))) goto failed; // 9×9将棋盤黒線テクスチャをバッファに書き込み

    return S_OK;

failed:
    return E_FAIL;
}

// レンダーテクスチャ作成
void DX12::CreateRenderTex()
{
    // 駒テクスチャ作成
    CreatePieceTex(ShogiObj::KING,   L"王",   L"");
    CreatePieceTex(ShogiObj::ROOK,   L"飛車", L"龍王");
    CreatePieceTex(ShogiObj::BISHOP, L"角行", L"龍馬");
    CreatePieceTex(ShogiObj::GOLD,   L"金将", L"");
    CreatePieceTex(ShogiObj::SILVER, L"銀将", L"成銀");
    CreatePieceTex(ShogiObj::KNIGHT, L"桂馬", L"成桂");
    CreatePieceTex(ShogiObj::LANCE,  L"香車", L"成香");
    CreatePieceTex(ShogiObj::PAWN,   L"歩",   L"と");

    // リソース開放
    for (auto& wrappedPieceTexBuff : _wrappedPieceTexBuffs) 
        wrappedPieceTexBuff.reset(); // ラップされたレンダーテクスチャバッファ
    _texRTVHeap.reset(); // テクスチャ用RTVヒープ
}




// 駒テクスチャ作成
void DX12::CreatePieceTex(
    ShogiObj::ShogiObjType shogiObjType,
    std::wstring frontText,
    std::wstring backText)
{
    InitRenderTex(shogiObjType); // テクスチャへのレンダリング初期処理
    
    auto wrappedRenderTexBuff = _wrappedPieceTexBuffs[shogiObjType].get();         // ラップされたバッファ
    auto d2dRenderTarget = _d2dPieceTexRenderTargets[shogiObjType].get(); // レンダーターゲット

    StartD2D(wrappedRenderTexBuff, d2dRenderTarget); // Direct2D開始
    
    auto size = 256 / 2;
    D2D1_RECT_F rect = {0, 5, size, size};
    _d2dDeviceContext->DrawTextW( // 黒色で駒表面を描画
        frontText,
        rect,
        _pieceTextFormat->GetTextFormat(),
        _blackBrush->GetBrush());

    rect.left += size;
    rect.right += size;
    _d2dDeviceContext->DrawTextW( // 赤色で駒裏面を描画
        backText,
        rect,
        _pieceTextFormat->GetTextFormat(),
        _redBrush->GetBrush());

    EndD2D(wrappedRenderTexBuff); // Direct2D終了

    ExitRenderTex(shogiObjType); // レンダリング終了処理
}

// テクスチャへのレンダリング初期処理
void DX12::InitRenderTex(ShogiObj::ShogiObjType shogiObjType)
{
    // テクスチャのリソースバリアをレンダーターゲットに変更
    auto renderTexBuff = _shogiObjTexBuffs[shogiObjType]->GetBuff();
    auto resourceBarrier = _rb->GetRBTexToRenderTarget(renderTexBuff);
    _cmdList->SetResourceBarrier(resourceBarrier);

    // レンダーターゲットに設定
    auto rtvHandle = _texRTVHeap->GetDescHandle(shogiObjType);
    _cmdList->SetRenderTarget(rtvHandle);

    _cmdList->ClearRenderTarget(rtvHandle); // レンダーターゲットクリア

    ExeCmd(); // コマンド実行
}

// Direct2D開始
void DX12::StartD2D(WrappedBuff* wrappedBuff, D2DRenderTarget* d2dRenderTarget)
{
    _device11->AcquireWrappedBuff(wrappedBuff);
    _d2dDeviceContext->SetRenderTarget(d2dRenderTarget);
    _d2dDeviceContext->BeginDraw();
    _d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
}

// Direct2D終了
void DX12::EndD2D(WrappedBuff* wrappedBuff)
{
    _d2dDeviceContext->EndDraw();
    _device11->ReleaseWrappedBuff(wrappedBuff);
    _deviceContext->Flash(); // Direct2D描画
}

// テクスチャへのレンダリング終了処理
void DX12::ExitRenderTex(ShogiObj::ShogiObjType shogiObjType)
{
    // テクスチャのリソースバリアをテクスチャに戻す
    auto renderTexBuff = _shogiObjTexBuffs[shogiObjType]->GetBuff();
    auto resourceBarrier = _rb->GetRBRenderTargetToTex(renderTexBuff);
     _cmdList->SetResourceBarrier(resourceBarrier);

    ExeCmd(); // コマンド実行
}


///////////////////////////////////////////////////////////////////////


// コマンド実行
void DX12::ExeDX12()
{
    
    _currentBackBuffIdx = _swapChain->GetCurrentBackBufferIdx(); // バックバッファインデックス取得
    
    InitRenderTarget(); // レンダーターゲット初期処理
    ExeD3D(); // Direct3D処理実行
    ExeD2D(); // Direct2D処理実行
    PrepareRenderTargetToFlip(); // 画面フリップ準備処理
    _swapChain->Flip(); // 画面フリップ
}

// レンダーターゲット初期処理
void DX12::InitRenderTarget()
{
    // バックバッファリソースをレンダーターゲットに変更
    auto resourceBarrier = _rb->GetRBToRenderTarget(_backBuffs[_currentBackBuffIdx]->GetBuff());
    _cmdList->SetResourceBarrier(resourceBarrier);

    // バックバッファをレンダーターゲットに設定
    auto rtvHandle = _rtvHeap->GetDescHandle(_currentBackBuffIdx);
    auto dsvHandle = _dsvHeap->GetDescHandle(0);
    _cmdList->SetRenderTarget(rtvHandle, dsvHandle);

    // クリア処理
    _cmdList->ClearRenderTarget(rtvHandle); // レンダーターゲットクリア
    _cmdList->ClearDepthStencil(dsvHandle); // デプスステンシルクリア
}




// Direct3D処理実行
void DX12::ExeD3D()
{
    auto& app    = Application::GetInstance();
    auto  board  = app.GetBoard();
    auto& pieces = app.GetPieces();
    auto boardVertIndices = app.GetBoardVertIndices();
    auto pieceVertIndices = app.GetPieceVertIndices();

    auto mainCamera = app.GetMainCamera();
    auto mapCamera = app.GetMapCamera();

    Set3DCmd(); // 3Dコマンドセット

    // ビューポートセット
    D3D12_VIEWPORT viewports[] = {*_mainViewport.get()};
    _cmdList->SetViewports(1, viewports);

    // シザー矩形セット
    D3D12_RECT scissorRects[] = {*_mainScissorRect.get()};
    _cmdList->SetScissorRects(1, scissorRects);

    // 将棋盤描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(boardVertIndices));
    _cmdList->SetVertBuffView(GetVertBuffView(board));
    _cmdList->SetDrawWithIdx(boardVertIndices);

    // 駒描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(pieceVertIndices));
    for (UINT i = 0; i < pieces.size(); i++)
    {
        _cmdList->SetVertBuffView(GetVertBuffView(pieces[i].get()));
        _cmdList->SetDrawWithIdx(pieceVertIndices);
    }

    // コンスタントバッファに書き込み
    _constBuff->WriteToConstBuff(
        board,
        pieces,
        mainCamera);

    ExeCmd(); // コマンド実行



    if (Application::GetInstance().IsDrawMap())
    {
        // バックバッファをレンダーターゲットに設定
        auto rtvHandle = _rtvHeap->GetDescHandle(_currentBackBuffIdx);
        auto dsvHandle = _dsvHeap->GetDescHandle(0);
        _cmdList->SetRenderTarget(rtvHandle, dsvHandle);

        // クリア処理
        //_cmdList->ClearRenderTarget(rtvHandle); // レンダーターゲットクリア
        _cmdList->ClearDepthStencil(dsvHandle); // デプスステンシルクリア

        Set3DCmd(); // 3Dコマンドセット

        // ビューポートセット
        viewports[0] = {*_mapViewport.get()};
        _cmdList->SetViewports(1, viewports);

        // シザー矩形セット
        scissorRects[0] = {*_mapScissorRect.get()};
        _cmdList->SetScissorRects(1, scissorRects);

        // 将棋盤描画コマンドセット
        _cmdList->SetIdxBuffView(GetIdxBuffView(boardVertIndices));
        _cmdList->SetVertBuffView(GetVertBuffView(board));
        _cmdList->SetDrawWithIdx(boardVertIndices);

        // 駒描画コマンドセット
        _cmdList->SetIdxBuffView(GetIdxBuffView(pieceVertIndices));
        for (UINT i = 0; i < pieces.size(); i++)
        {
            _cmdList->SetVertBuffView(GetVertBuffView(pieces[i].get()));
            _cmdList->SetDrawWithIdx(pieceVertIndices);
        }

        // コンスタントバッファに書き込み
        _constBuff->WriteToConstBuff(
            board,
            pieces,
            mapCamera);

        ExeCmd(); // コマンド実行
    }
    


    
}

// 3Dコマンドセット
void DX12::Set3DCmd()
{
    // パイプラインセット
    _cmdList->SetPipeline(_pipeline->GetPipelineState());

    // ルートシグネチャセット
    _cmdList->SetRootSignature(_rootSignature->GetRootSignature());

    // CSUヒープセット
    ID3D12DescriptorHeap* csuHeaps[] = {_csuHeap->GetHeap()};
    auto csuHeapNum = sizeof(csuHeaps) / sizeof(ID3D12DescriptorHeap*);
    _cmdList->SetCSUHeaps(1, csuHeaps); 

    // ルートパラメータとディスクリプタ関連付け
    _cmdList->SetDescriptorTable(0, _csuHeap->GetGPUCBVHandle(0)); // CBV
    _cmdList->SetDescriptorTable(1, _csuHeap->GetGPUSRVHandle(0)); // SRV

    // トポロジーセット
    _cmdList->SetTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertBuffView(ShogiObj* shogiObj)
{
    D3D12_VERTEX_BUFFER_VIEW view;

    auto buffAddress = _vertBuff->GetBuff()->GetGPUVirtualAddress();
    //buffAddress += shogiObj->GetVertices()->GetVertByteSize() * shogiObj->GetStartVertIdxInBuff();
    buffAddress += sizeof(GameObj::Vert) * shogiObj->GetStartVertIdxInBuff();

    view.BufferLocation =  // 頂点バッファのスタート位置
        //shogiObj->GetVertBuffAddress();
        buffAddress;
    view.StrideInBytes =   // 頂点1つ分のサイズ
        sizeof(GameObj::Vert);
    view.SizeInBytes = // 頂点全体のサイズ
        sizeof(GameObj::Vert) * shogiObj->GetVertices().size();

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIdxBuffView(VertIndices* vertIndices)
{
    D3D12_INDEX_BUFFER_VIEW view;

    view.BufferLocation = // インデックスバッファのスタート位置
        vertIndices->GetBuffAddress();
    view.Format =         // フォーマット unsigned short
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =    // インデックス全体のサイズ
        vertIndices->GetVertIndicesByteSize();

    return view;
}


// コマンド実行
void DX12::ExeCmd()
{
    _cmdList->Close(); // コマンドクローズ
    _cmdQueue->ExeCmd(_cmdList.get()); // コマンド実行
    WaitProcessWithFence(); // フェンスによる同期処理
    _cmdAllocator->Reset();               // コマンドアロケータリセット
    _cmdList->Reset(_cmdAllocator.get()); // コマンドリストリセット
}



// Direct2D処理実行
void DX12::ExeD2D()
{
    auto wrappedBackBuff = _wrappedBackBuffs[_currentBackBuffIdx].get();
    auto d2dRenderTarget = _d2dRenderTargets[_currentBackBuffIdx].get();
    auto uis = Application::GetInstance().GetUIs();
    StartD2D(wrappedBackBuff, d2dRenderTarget); // Direct2D開始

    for (auto& ui : uis)
    {
        // 四角形描画
        _d2dDeviceContext->DrawRectangle(
            ui.GetRect(),
            _uiBrush->GetBrush(),
            _blackBrush->GetBrush());

        // テキスト描画　選択されていたら赤色
        auto brushColor = ui.IsSelected() ? _redBrush->GetBrush() : _blackBrush->GetBrush();
        _d2dDeviceContext->DrawTextW(
        ui.GetText(),
        ui.GetRect(),
        _uiTextFormat->GetTextFormat(),
        brushColor);
    }
        
    EndD2D(wrappedBackBuff); // Direct2D終了
}




// レンダーターゲットのフリップ準備
void DX12::PrepareRenderTargetToFlip()
{
    // バックバッファを表示画面に設定
    auto resourceBarrier = _rb->GetRBToPresent(_backBuffs[_currentBackBuffIdx]->GetBuff());
    _cmdList->SetResourceBarrier(resourceBarrier);

    ExeCmd(); // コマンド実行
}






// フェンスによる同期制御
void DX12::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _cmdQueue->GetCmdQueue()->Signal(_fence->GetFence(), _fence->GetIncrementFenceVal());

    while (_fence->GetFence()->GetCompletedValue() != _fence->GetFenceVal())
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->GetFence()->SetEventOnCompletion(_fence->GetFenceVal(), event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}




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





//ViewMat* DX12::GetViewMat(){return _viewMat.get();} // ビュー行列を返す




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

    _dxgiFactory = std::make_unique<DXGIFactory>();
    _adapter     = std::make_unique<Adapter>();
    _device      = std::make_unique<Device>();

    _rtvHeap      = std::make_unique<Heap>();
    _texRTVHeap   = std::make_unique<Heap>();
    _csuHeap       = std::make_unique<CSUHeap>();

    _dWriteFactory = std::make_unique<DWriteFactory>();
    _device11      = std::make_unique<Device11>();
    _deviceContext = std::make_unique<DeviceContext>();
    _d2dDeviceContext = std::make_unique<D2DDeviceContext>();

    // ブラシ
    _blackBrush = std::make_unique<Brush>();
    _redBrush   = std::make_unique<Brush>();
    _uiBrush    = std::make_unique<Brush>();

    _pieceTextFormat = std::make_unique<TextFormat>();
    _uiTextFormat = std::make_unique<TextFormat>();

    _cmdAllocator = std::make_unique<CmdAllocator>();
    _cmdList      = std::make_unique<CmdList>();
    _cmdQueue     = std::make_unique<CmdQueue>();

    _swapChain = std::make_unique<SwapChain>();

    

    _dsBuff  = std::make_unique<Buff>();
    _dsvHeap = std::make_unique<Heap>();

    _fence = std::make_unique<Fence>();

    _mainViewport    = std::make_unique<D3D12_VIEWPORT>();
    _mainScissorRect = std::make_unique<D3D12_RECT>();
    _mapViewport     = std::make_unique<D3D12_VIEWPORT>();
    _mapScissorRect  = std::make_unique<D3D12_RECT>();

    _vShader       = std::make_unique<VShader>();
    _pShader       = std::make_unique<PShader>();
    _vertBuff      = std::make_unique<Buff>();
    _idxBuff       = std::make_unique<IdxBuff>();
    _constBuff     = std::make_unique<ConstBuff>();
    _woodTexBuff       = std::make_unique<TexBuff>();

    
    _rootSignature = std::make_unique<RootSignature>();
    _inputLayout   = std::make_unique<InputLayout>();
    _pipeline      = std::make_unique<Pipeline>();

    _pieceTexRTVHeap = std::make_unique<Heap>();
    _pieceTexSRVHeap = std::make_unique<CSUHeap>();

    _rb = std::make_unique<ResourceBarrier>();
}