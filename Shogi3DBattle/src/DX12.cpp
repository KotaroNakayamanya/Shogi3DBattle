#include"DX12.h"

#include"Application.h"
#include<algorithm>
#include<cassert>
#include<Pawn.h>

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

    //// 駒テクスチャ作成
    //UINT shogiTexNum;
    //shogiTexNum = 8 + 6 + 1; // 駒表8種 駒裏6種 将棋盤1
    //_pieceTexBuffs.resize(shogiTexNum);
    //for (UINT i = 0; i < shogiTexNum; i++)
    //{
    //    _pieceTexBuffs[i] = std::make_unique<RenderTexBuff>();
    //    if (FAILED(_device->CreateRenderTexBuff(_pieceTexBuffs[i].get(), _backBuffs[0].get()))) goto failed; // レンダーターゲットテクスチャ作成
    //}
    //// if (FAILED(_device->CreateRTVHeap(_rtvHeap.get(), _swapChain.get()))) goto failed; // 駒テクスチャRTVヒープ作成
    
    // ルートシグネチャオブジェクト作成
    if (FAILED(_device->CreateRootSignature(_rootSignature.get(), _csuHeap.get()))) goto failed;

    // 頂点バッファ入力レイアウト作成
    _device->CreateInputLayout(_inputLayout.get());
    // シェーダー系作成
    if(FAILED(CreateShader())) goto failed;

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
    
    auto  gameWindow = app.GetGameWindow(); // ゲームウインドウ取得
    auto  board      = app.GetBoard();
    auto& pieces     = app.GetPieces();
    auto  woodTex = app.GetWoodTex();
    auto  boardLineTex = app.GetBoardLineTex();
    

    UINT widthSize, heightSize;

    // バックバッファ作成
    _backBuffs.resize(_swapChain->GetBackBuffNum());
    for (UINT i = 0; i < _backBuffs.size(); i++)
    {
        _backBuffs[i] = std::make_unique<Buff>();
        if (FAILED(_swapChain->CreateBackBuff(_backBuffs[i].get(), i))) goto failed;
    }

    // デプスステンシルバッファ作成
    widthSize  = gameWindow->GetWindowWidth();
    heightSize = gameWindow->GetWindowHeight();
    if (FAILED(_device->CreateBuff(_dsBuff.get(), widthSize, heightSize, Buff::DEPTH_STENCIL))) goto failed;

    // コンスタントバッファ作成
    widthSize  = (sizeof(DirectX::XMMATRIX)*(40+1+1) + 0xff) & ~0xff; // 駒40 将棋盤1 ビュープロジェクション行列1 256アラインメント
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_constBuff.get(), widthSize, heightSize, Buff::CONSTANT))) goto failed;

    // 頂点バッファ作成
    widthSize = board->GetVerticesByteSize();
    for(auto& piece : pieces) {widthSize += piece->GetVerticesByteSize(); }
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_vertBuff.get(), widthSize, heightSize, Buff::VERTEX))) goto failed;

    // インデックスバッファ作成
    widthSize = board->GetIndicesByteSize();
    for(auto& piece : pieces) {widthSize += piece->GetIndicesByteSize(); }
    heightSize = 1;
    if (FAILED(_device->CreateBuff(_idxBuff.get(), widthSize, heightSize, Buff::INDEX))) goto failed;

    // 木材テクスチャバッファ作成
    widthSize  = woodTex->GetWidth();
    heightSize = woodTex->GetHeight();
    if (FAILED(_device->CreateBuff(_woodTexBuff.get(), widthSize, heightSize, Buff::TEXTURE))) goto failed;

    // 将棋盤黒線テクスチャバッファ作成
    widthSize  = boardLineTex->GetWidth();
    heightSize = boardLineTex->GetHeight();
    if (FAILED(_device->CreateBuff(_boardLineTexBuff.get(), widthSize, heightSize, Buff::TEXTURE))) goto failed;

    // 歩テクスチャバッファ作成
    widthSize  = boardLineTex->GetWidth();
    heightSize = boardLineTex->GetHeight();
    if (FAILED(_device->CreateBuff(_pawnTexBuff.get(), widthSize, heightSize, Buff::RENDER_TEX))) goto failed;

    return S_OK;

failed:
    return E_FAIL;
}

// ヒープ作成
HRESULT DX12::CreateHeap()
{
    if (FAILED(_device->CreateHeap(_rtvHeap.get(), _swapChain->GetBackBuffNum(), Heap::RTV))) goto failed; // RTVヒープ作成
    if (FAILED(_device->CreateHeap(_texRTVHeap.get(), 1, Heap::RTV))) goto failed; // テクスチャRTVヒープ作成
    if (FAILED(_device->CreateHeap(_dsvHeap.get(), 1, Heap::DSV))) goto failed; // DSVヒープ作成

    UINT cbvNum, srvNum, uavNum;
    cbvNum = 1;
    srvNum = 3;
    uavNum = 0;
    if (FAILED(_device->CreateCSUHeap(_csuHeap.get(), cbvNum, srvNum, uavNum, Heap::CSU))) goto failed; // CSUヒープオブジェクト作成

    return S_OK;

failed:
    return E_FAIL;
}

// ビュー作成
void DX12::CreateView()
{
    for (UINT i = 0; i < _rtvHeap->GetDescNum(); i++)
    {
        _device->CreateView(_rtvHeap.get(), i, _backBuffs[i].get(), View::RTV); // RTV作成
    }
    for (UINT i = 0; i < _texRTVHeap->GetDescNum(); i++)
    {
        _device->CreateView(_texRTVHeap.get(), i, _pawnTexBuff.get(), View::RTV); // テクスチャRTV作成
    }
    for (UINT i = 0; i < _dsvHeap->GetDescNum(); i++)
    {
        _device->CreateView(_dsvHeap.get(), i, _dsBuff.get(), View::DSV); // DSV作成
    }
    for (UINT i = 0; i < _csuHeap->GetCBVNum(); i++)
    {
        _device->CreateCSUView(_csuHeap.get(), i, _constBuff.get(), View::CBV); // CBV作成
    }
    //for (UINT i = 0; i < _csuHeap->GetSRVNum(); i++)
    //{
    //    _device->CreateCSUView(_csuHeap.get(), 0, _texBuff.get(), View::SRV);   // SRV作成
    //}

    _device->CreateCSUView(_csuHeap.get(), 0, _woodTexBuff.get(), View::SRV);   // SRV作成
    _device->CreateCSUView(_csuHeap.get(), 1, _boardLineTexBuff.get(), View::SRV);   // SRV作成
    _device->CreateCSUView(_csuHeap.get(), 2, _pawnTexBuff.get(), View::SRV);   // SRV作成

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

    _viewport->SetViewport(gameWindow); // ビューポート作成
    _scissorRect->SetScissorRect(gameWindow); // シザー矩形作成
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
        if (FAILED(_device11->CreateWrappedBuff(_wrappedBackBuffs[i].get(), _backBuffs[i].get()))) goto failed;
    }
    for (UINT i = 0; i < backBuffNum; i++)
    {
        // Direct2Dレンダーターゲット作成
        _d2dRenderTargets[i] = std::make_unique<D2DRenderTarget>();
        if (FAILED(_d2dDeviceContext->CreateD2DRenderTarget(_d2dRenderTargets[i].get(), _wrappedBackBuffs[i].get()))) goto failed;
    }

    // ラップされたテクスチャバッファ作成
    if (FAILED(_device11->CreateWrappedBuff(_wrappedPawnTexBuff.get(), _pawnTexBuff.get()))) goto failed;
    // Direct2Dレンダーターゲット作成
    if (FAILED(_d2dDeviceContext->CreateD2DRenderTarget(_d2dRenderTargetPawnTex.get(), _wrappedPawnTexBuff.get()))) goto failed;

    // DirectWriteファクトリー作成
    if (FAILED(CreateDWriteFactory())) goto failed;
    // ソリッドカラーブラッシュ作成
    if(FAILED(_d2dDeviceContext->CreateD2DSolidColorBrush(_d2dSolidColorBrush.get()))) goto failed;
    // テキストフォーマット作成
    if(FAILED(_dWriteFactory->CreateDWriteTextFormat(_dWriteTextFormat.get(), L"メイリオ"))) goto failed;
    // if(FAILED(_dWriteFactory->CreateDWriteTextFormat(_pieceTextFormat.get(), L"メイリオ"))) goto failed; // 駒のテキストフォーマット作成

    return S_OK;

failed:
    return E_FAIL;
}

// レンダーテクスチャ作成
void DX12::CreateRenderTex()
{
    InitRenderTex(); // レンダーテクスチャ初期処理
    ExeD3D(); // Direct3D処理実行
    ExeD2D(); // Direct2D処理実行
    PrepareRenderTargetToFlip(); // 画面フリップ準備処理
    _swapChain->Flip(); // 画面フリップ

    ExeCmd(); // コマンド実行してリソースをレンダーターゲットにする

    _device11->AcquireWrappedBuff(_wrappedPawnTexBuff.get());
    _d2dDeviceContext->SetRenderTarget(_d2dRenderTargetPawnTex.get());
    _d2dDeviceContext->BeginDraw();
    _d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

    DrawStr(L"歩", 0, 30, 256/2-1, 256/2-1);
    DrawStr(L"と", 256/2, 30, 256, 256/2-1);

    _d2dDeviceContext->EndDraw();
    _device11->ReleaseWrappedBuff(_wrappedPawnTexBuff.get());
    _deviceContext->Flash(); // Direct2D描画

    ExeRenderToTex(); // テクスチャへレンダリング実行
}

// レンダーテクスチャ初期処理
void DX12::InitRenderTex()
{
    // テクスチャのリソースバリアをレンダーターゲットに変更
    auto resourceBarrier = _rb->GetRBTexToRenderTarget(_pawnTexBuff->GetBuff());
    _cmdList->SetResourceBarrier(resourceBarrier);

    // レンダーターゲットに設定
    auto rtvHandle = _texRTVHeap->GetDescHandle(0);
    _cmdList->SetRenderTarget(rtvHandle);

    _cmdList->ClearRenderTarget(rtvHandle); // レンダーターゲットクリア
}

// テクスチャへレンダリング実行
void DX12::ExeRenderToTex()
{
    // テクスチャのリソースバリアをテクスチャに戻す
    auto resourceBarrier = _rb->GetRBRenderTargetToTex(_pawnTexBuff->GetBuff());
     _cmdList->SetResourceBarrier(resourceBarrier);
    // コマンド実行
    ExeCmd();
}

// バッファに書き込み
HRESULT DX12::WriteToBuff()
{
    auto& app    = Application::GetInstance();
    auto  board  = app.GetBoard();
    auto& pieces = app.GetPieces();
    auto  woodTex = app.GetWoodTex();
    auto  boardLineTex = app.GetBoardLineTex();

    if (FAILED(_vertBuff->WriteToVertBuff(board, pieces))) goto failed; // 頂点バッファに書き込み
    if (FAILED(_idxBuff ->WriteToIdxBuff (board, pieces)))  goto failed; // インデックスバッファに書き込み
    _woodTexBuff->WriteToTexBuff(woodTex); // 木材テクスチャをバッファに書き込み
    _boardLineTexBuff->WriteToTexBuff(boardLineTex); // 将棋盤黒線テクスチャをバッファに書き込み

    return S_OK;

failed:
    return E_FAIL;
}


///////////////////////////////////////////////////////////////////////


// コマンド実行
void DX12::ExeDX12()
{
    InitRenderTarget(); // レンダーターゲット初期処理
    ExeD3D(); // Direct3D処理実行
    //ExeD2D(); // Direct2D処理実行
    PrepareRenderTargetToFlip(); // 画面フリップ準備処理
    _swapChain->Flip(); // 画面フリップ
}

// レンダーターゲット初期処理
void DX12::InitRenderTarget()
{
    // バックバッファインデックス取得
    _currentBackBuffIdx = _swapChain->GetCurrentBackBufferIdx();

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
    Set3DCmd(); // 3Dコマンドセット

    auto& app    = Application::GetInstance();
    auto  board  = app.GetBoard();
    auto& pieces = app.GetPieces();

    // 将棋盤描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(board));
    SetDrawObjCmd(board);

    // 駒描画コマンドセット
    _cmdList->SetIdxBuffView(GetIdxBuffView(pieces[0].get())); // 駒のインデックスは全部同じ
    for (UINT i = 0; i < pieces.size(); i++)
    {
        SetDrawObjCmd(pieces[i].get());
    }

    // ワールド行列、ビュープロジェクション行列をコンスタントバッファに書き込み
    _constBuff->WriteToConstBuff(
        board,
        pieces,
        _viewMat.get(),
        _projMat.get());

    ExeCmd(); // コマンド実行
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

    // ビューポートセット
    D3D12_VIEWPORT viewports[] = {_viewport->GetViewport()};
    _cmdList->SetViewports(1, viewports);

    // シザー矩形セット
    D3D12_RECT scissorRects[] = {_scissorRect->GetScissorRect()};
    _cmdList->SetScissorRects(1, scissorRects);
}

// オブジェクト描画コマンドセット
void DX12::SetDrawObjCmd(ShogiObj* shogiObj)
{
    // 頂点バッファビューセット
    _cmdList->SetVertBuffView(GetVertBuffView(shogiObj));
    // インデックス描画セット
    _cmdList->SetDrawWithIdx(shogiObj);
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertBuffView(ShogiObj* shogiObj)
{
    D3D12_VERTEX_BUFFER_VIEW view;

    view.BufferLocation =  // 頂点バッファのスタート位置
        shogiObj->GetVertAddress();
    view.StrideInBytes =   // 頂点1つ分のサイズ
        shogiObj->GetVertexByteSize();
        view.SizeInBytes = // 頂点全体のサイズ
        shogiObj->GetVerticesByteSize();

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIdxBuffView(ShogiObj* shogiObj)
{
    D3D12_INDEX_BUFFER_VIEW view;

    view.BufferLocation = // インデックスバッファのスタート位置
        shogiObj->GetIdxAddress();
    view.Format =         // フォーマット unsigned short
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =    // インデックス全体のサイズ
        shogiObj->GetIndicesByteSize();

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
    StartD2D(); // Direct2D開始
    DrawStr(L"歩りゃあ", 0, 0, 720, 720);
    EndD2D(); // Direct2D終了
}

// Direct2D開始
void DX12::StartD2D()
{
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    _device11->AcquireWrappedBuff(_wrappedBackBuffs[backBufferIdx].get());
    _d2dDeviceContext->SetRenderTarget(_d2dRenderTargets[backBufferIdx].get());
    _d2dDeviceContext->BeginDraw();
    _d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
}

// Direct2D終了
void DX12::EndD2D()
{
    auto backBufferIdx = _swapChain->GetCurrentBackBufferIdx();

    _d2dDeviceContext->EndDraw();
    _device11->ReleaseWrappedBuff(_wrappedBackBuffs[backBufferIdx].get());
    _deviceContext->Flash(); // Direct2D描画
}

// 文字を出力する
void DX12::DrawStr(
    std::wstring str,
    float left,
    float top,
    float right,
    float bottom)
{
    D2D1_RECT_F rect = {left, top, right, bottom};

    _d2dDeviceContext->DrawTextW(
        str,
        rect,
        _dWriteTextFormat->GetDWriteTextFormat(),
        _d2dSolidColorBrush->GetD2DSolidColorBrush());
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




//////
//Piece* DX12::GetPawn(){return _pieces[0].get(); } // 歩を返す}
ViewMat* DX12::GetViewMat(){return _viewMat.get();} // ビュー行列を返す
//////



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

    _viewMat = std::make_unique<ViewMat>();
    _projMat = std::make_unique<ProjMat>();

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
    _d2dSolidColorBrush = std::make_unique<D2DSolidColorBrush>();
    _dWriteTextFormat = std::make_unique<DWriteTextFormat>();
    _pieceTextFormat = std::make_unique<DWriteTextFormat>();

    _cmdAllocator = std::make_unique<CmdAllocator>();
    _cmdList      = std::make_unique<CmdList>();
    _cmdQueue     = std::make_unique<CmdQueue>();

    _swapChain = std::make_unique<SwapChain>();

    

    _dsBuff  = std::make_unique<Buff>();
    _dsvHeap = std::make_unique<Heap>();

    _fence = std::make_unique<Fence>();

    _viewport    = std::make_unique<Viewport>();
    _scissorRect = std::make_unique<ScissorRect>();

    _vShader       = std::make_unique<VShader>();
    _pShader       = std::make_unique<PShader>();
    _vertBuff      = std::make_unique<VertBuff>();
    _idxBuff       = std::make_unique<IdxBuff>();
    _constBuff     = std::make_unique<ConstBuff>();
    _woodTexBuff       = std::make_unique<TexBuff>();
    _boardLineTexBuff       = std::make_unique<TexBuff>();
    _pawnTexBuff       = std::make_unique<TexBuff>();

    
    _rootSignature = std::make_unique<RootSignature>();
    _inputLayout   = std::make_unique<InputLayout>();
    _pipeline      = std::make_unique<Pipeline>();

    _pieceTexRTVHeap = std::make_unique<Heap>();
    _pieceTexSRVHeap = std::make_unique<CSUHeap>();

    _rb = std::make_unique<ResourceBarrier>();

    _wrappedPawnTexBuff = std::make_unique<WrappedBuff>();
    _d2dRenderTargetPawnTex = std::make_unique<D2DRenderTarget>();
}

DX12::~DX12(){}