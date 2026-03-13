#include"DX12.h"

#include<algorithm>
#include<cassert>

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


// DirectX12初期設定
bool DX12::CreateDX12Obj(HWND hwnd)
{
    if (FAILED(CreateDXGIFactory())) goto failed; // DXGIファクトリーオブジェクト作成
    if (FAILED(_dxgiFactory->CreateAdapter(_adapter.get()))) goto failed; // アダプターオブジェクト作成
    if (FAILED(_dxgiFactory->CreateDevice(_device.get(), _adapter.get()))) goto failed; // デバイスオブジェクト作成

    _adapter.reset(); // アダプター破棄

    // 描画オブジェクト作成
    if (FAILED(CreateDrawObj(hwnd))) goto failed;
    if (FAILED(_device->CreateVShader(_vShader.get()))) goto failed; // 頂点シェーダーバイナリオブジェクト作成
    if (FAILED(_device->CreatePShader(_pShader.get()))) goto failed; // ピクセルシェーダーバイナリオブジェクト作成
    // 頂点集合作成
    if (FAILED(CreateVertexSets())) goto failed;
    if (FAILED(_device->CreateVertBuff(_vertBuff.get(), _pawn->GetVerticesByteSize()))) goto failed; // 頂点バッファオブジェクト作成
    if (FAILED(_device->CreateIdxBuff (_idxBuff.get(),  _pawn->GetVerticesByteSize()))) goto failed; // インデックスバッファオブジェクト作成
    
    if (FAILED(_vertBuff->WriteVertBuff(_pawn->GetVerticesPtr()))) goto failed; // 頂点バッファに書き込み
    if (FAILED(_idxBuff->WriteIdxBuff  (_pawn->GetIndicesPtr())))  goto failed; // インデックスバッファに書き込み

    
    if (FAILED(_device->CreateTexBuff(_texBuff.get()))) goto failed; // テクスチャオブジェクト作成
    if (FAILED(_device->CreateConstBuff(_constBuff.get(), _pawn->GetVerticesByteSize()))) goto failed; // コンスタントバッファオブジェクト作成

    if (FAILED(_constBuffMap->MapConstBuff(_constBuff->GetBuff()))) goto failed; // コンスタントバッファをマップ

    // CSUヒープオブジェクト作成
    if (FAILED(CreateCSUHeapObj())) goto failed;

    // ルートシグネチャオブジェクト作成
    if (FAILED(CreateRootSignatureObj())) goto failed;
    // パイプラインオブジェクト作成
    if (FAILED(CreatePipelineObj())) goto failed;

    return true;

failed:
    assert(false);
    return false;
}

// DXGIファクトリー作成
HRESULT DX12::CreateDXGIFactory()
{
    HRESULT result;

    // デバッグモードのときは詳細を表示させるファクトリーを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory->_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory->_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}

// 描画オブジェクト作成（Drawクラス）
HRESULT DX12::CreateDrawObj(HWND hwnd)
{
    _draw = std::make_unique<Draw>(_buffNum);

    DrawArg::CreateDrawObjArg arg =
        GetCreateDrawObjArg(hwnd);

    return _draw->CreateDrawObj(arg);
}

// 描画オブジェクト作成用引数
DrawArg::CreateDrawObjArg DX12::GetCreateDrawObjArg(HWND hwnd)
{
    DrawArg::CreateDrawObjArg arg = {};

    arg.device =
        _device->GetDevice();
    arg.dxgiFactoryObj =
        _dxgiFactory.get();
    arg.hwnd =
        hwnd;
    arg.windowWidth = 1280; // 初期値
    arg.windowHeight = 720; // 初期値
    arg.buffNum = _buffNum;

    return arg;
}

// ヒープ作成
HRESULT DX12::CreateCSUHeapObj()
{
    _csuHeap = std::make_unique<CSUHeap>();

    HeapArg::CreateCSUHeapArg arg = GetCreateCSUHeapArg();
    return _csuHeap->CreateHeap(arg);
}

// CSVヒープ作成用引数
HeapArg::CreateCSUHeapArg DX12::GetCreateCSUHeapArg()
{
    HeapArg::CreateCSUHeapArg arg = {};

    arg.device = _device->GetDevice();
    arg.buff1 = _constBuff->GetBuff();
    arg.buff2 = _texBuff->GetTexBuff();
  //arg.buff3 = nullptr;

    return arg;
}

// 頂点集合作成
HRESULT DX12::CreateVertexSets()
{

    /*std::for_each(_objects.begin(), _objects.end(),
        [](std::unique_ptr<Object>& object)
        {
            object = std::make_unique<Object>();
        });*/
    _pawn = std::make_unique<Pawn>();

    return S_OK;
}

// サンプリングディスクリプタ
DXGI_SAMPLE_DESC DX12::GetSampleDesc()
{
    DXGI_SAMPLE_DESC desc = {};

    desc.Count   = 1; // サンプリング数
    desc.Quality = 0; // クオリティ（0は最低）

    return desc;
}

// ルートシグネチャオブジェクト作成
HRESULT DX12::CreateRootSignatureObj()
{
    _rootSignature = std::make_unique<RootSignature>();

    return _rootSignature->CreateRootSignatureObj(_device->GetDevice());
}

// パイプラインオブジェクト作成
HRESULT DX12::CreatePipelineObj()
{
    _pipeline = std::make_unique<Pipeline>();

    PipelineArg::CreatePipelineStateArg arg =
        GetCreatePipelineObjArg();

    return _pipeline->CreatePipelineState(arg);
}

PipelineArg::CreatePipelineStateArg DX12::GetCreatePipelineObjArg()
{
    PipelineArg::CreatePipelineStateArg arg = {};

    arg.device = _device->GetDevice();
    arg.rootSignature = _rootSignature->GetRootSignature();
    arg.vertexShaderBlob = _vShader->GetVShaderBlob();
    arg.pixelShaderBlob  = _pShader->GetPShaderBlob();
    arg.sampleDesc = GetSampleDesc();

    return arg;
}




// コマンド実行
void DX12::ExeDX12()
{
    // レンダーターゲットの準備をする
    _draw->PrepareRenderTarget();

    // 頂点を変換
    _constBuffMap->WriteMat(
        _pawn->GetWorldMat(),
        _viewMat->GetViewMat(),
        _projMat->GetProjMat());

    // コマンドセット
    SetCommand();

    // 描画実行
    _draw->ExeDraw();
    return;
}

// コマンドセット（Drawクラス）
void DX12::SetCommand()
{
    DrawArg::SetCommandArg arg =
        GetSetCommandArg();

    _draw->SetCommand(arg);

}

// コマンドセット用引数
DrawArg::SetCommandArg DX12::GetSetCommandArg()
{
    DrawArg::SetCommandArg arg = {};

    arg.pipelineState =
        _pipeline->GetPipelineState();
    arg.rootSignature =
        _rootSignature->GetRootSignature();
    arg.csuHeap
        = _csuHeap->GetHeap();;
    arg.offset =
        _device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    arg.topology =
        D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    arg.vertexBuffView =
        GetVertexBuffView();
    arg.indexBuffView =
        GetIndexBuffView();
    arg.vertexCount
        = _pawn->GetIndicesNum();
    arg.objCount
        = 1;

    return arg;
}

// 頂点バッファビュー
D3D12_VERTEX_BUFFER_VIEW DX12::GetVertexBuffView()
{
    D3D12_VERTEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> vertexBuff =
        _vertBuff->GetVertBuff();

    UINT vertexByteSize   = _pawn->GetVertexByteSize();
    UINT verticesByteSize = _pawn->GetVerticesByteSize();

    view.BufferLocation =
        vertexBuff->GetGPUVirtualAddress();
    view.SizeInBytes =
        verticesByteSize; // 注意
    view.StrideInBytes =
        vertexByteSize; // 注意

    return view;
}

// インデックスバッファビュー
D3D12_INDEX_BUFFER_VIEW DX12::GetIndexBuffView()
{
    D3D12_INDEX_BUFFER_VIEW view;

    ComPtr<ID3D12Resource> indexBuff =
        _idxBuff->GetIdxBuff();

    UINT indicesByte = _pawn->GetIndicesByteSize();

    view.BufferLocation =
        indexBuff->GetGPUVirtualAddress();
    view.Format =
        DXGI_FORMAT_R16_UINT;
    view.SizeInBytes =
        indicesByte;

    return view;
}




//////
Piece* DX12::GetPawn(){return _pawn.get();} // 歩を返す}
ViewMat* DX12::GetViewMat(){return _viewMat.get();} // ビュー行列を返す
//////



// ウインドウサイズ変更処理
void DX12::ProcessChangeWindowSize(UINT width, UINT height)
{   
    // 画面サイズを更新
    _windowWidth  = width;
    _windowHeight = height;
    // スワップチェーン更新
    _draw->UpdateDrawConf(
        _device->GetDevice(),
        _windowWidth, 
        _windowHeight,
        _buffNum);
}

DX12::DX12() {
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _viewMat = std::make_unique<ViewMat>();
    _projMat = std::make_unique<ProjMat>();

    _dxgiFactory  = std::make_unique<DXGIFactory>();
    _adapter      = std::make_unique<Adapter>();
    _device       = std::make_unique<Device>();
    _vShader      = std::make_unique<VShader>();
    _pShader      = std::make_unique<PShader>();
    _vertBuff     = std::make_unique<VertBuff>();
    _idxBuff      = std::make_unique<IdxBuff>();
    _texBuff      = std::make_unique<TexBuff>();
    _constBuff    = std::make_unique<ConstBuff>();
    _constBuffMap = std::make_unique<ConstBuffMap>();
}

DX12::~DX12(){}