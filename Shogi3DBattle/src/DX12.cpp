#include"DX12.h"
#include"Vertex.h"
#include"Draw.h"

#include<algorithm>
#include<string>
#include<cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;

        D3D12GetDebugInterface(
            IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期設定
bool DX12::CreateDX12Object()
{
    // DXGIファクトリー作成
    if (FAILED(CreateFactory()))
    {
        assert(false); return false;
    }

    // 使用するアダプターを決定
    CreateUsedAdapterLists();
    DecisionUsingAdapter();

    // デバイス作成（GPU機能レベルに対応していなければ失敗）
    if (FAILED(CreateDevice()))
    {
        assert(false); return false;
    }

    // 描画オブジェクト作成
    if (FAILED(CreateDrawObject()))
    {
        assert(false); return false;
    }

    // レンダーターゲットビュー作成
    if (FAILED(CreateRTVHeap()))
    {
        assert(false); return false;
    }
    if (FAILED(CreateRTV()))
    {
        assert(false); return false;
    }

    // 頂点集合作成
    if (FAILED(CreateVertexSets()))
    {
        assert(false); return false;
    }

    // 頂点バッファ作成
    if (FAILED(CreateVertexBuffer()))
    {
        assert(false); return false;
    }

    // バッファに頂点をマップ
    if (FAILED(MapVertexToBuffer()))
    {
        assert(false); return false;
    }

    return true;
}

HRESULT DX12::CreateFactory()
{
    HRESULT result;
    // デバッグモードのときは詳細を表示させるものを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}

// 使われているアダプタ（GPU）を動的配列に入れる
void DX12::CreateUsedAdapterLists()
{
    ComPtr<IDXGIAdapter> tmpAdapter;
    int i = 0;
    while (_dxgiFactory->EnumAdapters(i, tmpAdapter.ReleaseAndGetAddressOf())
           != DXGI_ERROR_NOT_FOUND)
    {
        _adapters.push_back(tmpAdapter.Get());
        i++;
    }
}

// 使用するアダプターを決定
void DX12::DecisionUsingAdapter()
{
    for(auto adapter : _adapters)
    {
        // アダプター説明オブジェクト取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);

        std::wstring str = adapterDesc.Description;

        if (str.find(L"NVIDIA") != std::string::npos)
        {
            _usingAdapter.Swap(adapter);
            break;
        }
    }
}

// デバイス作成
HRESULT DX12::CreateDevice()
{
    HRESULT result;
    // GPU機能レベルの配列順にデバイス作成を試みる
    std::find_if(_featureLevels.begin(), _featureLevels.end(),
        [this, &result](D3D_FEATURE_LEVEL featureLevel)
        {
            result = D3D12CreateDevice(
                _usingAdapter.Get(),
                featureLevel,
                IID_PPV_ARGS(_device.ReleaseAndGetAddressOf()));

            return result == S_OK; // 作成できたら戻る
        });

    return result;
}

// 描画オブジェクト（コマンド、スワップチェーン、フェンス）を作成
HRESULT DX12::CreateDrawObject()
{
    _draw.reset(new Draw(_bufferNum));

    if (FAILED(CreateCommandAllocator()))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateCommandList()))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateCommandQueue()))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateSwapChain()))
    {
        assert(false); return E_FAIL;
    }
    if (FAILED(CreateFence()))
    {
        assert(false); return E_FAIL;
    }

    return S_OK;
}

HRESULT DX12::CreateCommandAllocator()
{
    auto commandAllocatorPtr = _draw->GetCommandAllocatorPtr();

    return _device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(commandAllocatorPtr));
}

HRESULT DX12::CreateCommandList()
{
    auto commandAllocatorPtr = _draw->GetCommandAllocatorPtr();
    auto commandListPtr      = _draw->GetCommandListPtr();

    return _device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        *commandAllocatorPtr,
        nullptr,
        IID_PPV_ARGS(commandListPtr));
}

HRESULT DX12::CreateCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc =
        GetCommandQueueDesc();

    auto commandQueuePtr = _draw->GetCommandQueuePtr();

    return _device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(commandQueuePtr));
}

D3D12_COMMAND_QUEUE_DESC DX12::GetCommandQueueDesc()
{
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type =    // コマンドリストタイプの種類
        D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = // アプリケーション優先度 通常
        D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = // タイムアウトなし
        D3D12_COMMAND_QUEUE_FLAG_NONE; 
    desc.NodeMask =
        0;

    return desc;
}

HRESULT DX12::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc();

    auto commandQueuePtr = _draw->GetCommandQueuePtr();
    auto swapChainPtr    = _draw->GetSwapChainPtr();

    return _dxgiFactory->CreateSwapChainForHwnd(
        *commandQueuePtr,
        _hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)swapChainPtr);
}

DXGI_SWAP_CHAIN_DESC1 DX12::GetSwapChainDesc()
{
    DXGI_SWAP_CHAIN_DESC1 desc = {};

    desc.Width =
        300;
    desc.Height =
        500;
    desc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo =
        false;
    desc.SampleDesc.Count =
        1;
    desc.SampleDesc.Quality =
        0;
    desc.BufferUsage =
        DXGI_USAGE_BACK_BUFFER;
    desc.BufferCount =
        _bufferNum;

    desc.Scaling =
        DXGI_SCALING_STRETCH;
    desc.SwapEffect =
        DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode =
        DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return desc;
}

HRESULT DX12::CreateFence()
{
    auto fencePtr = _draw->GetFencePtr();
    auto fenceVal = _draw->GetFenceVal();

    return _device->CreateFence(
        fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(fencePtr));
}

// レンダーターゲットビューヒープ作成
HRESULT DX12::CreateRTVHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetRTVHeapDesc();

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_rtvHeap.ReleaseAndGetAddressOf()));
}

// RTVヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC DX12::GetRTVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        _bufferNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
}

// レンダーターゲットビュー作成
HRESULT DX12::CreateRTV()
{
    // ヒープの先頭アドレスを取得しておく
    D3D12_CPU_DESCRIPTOR_HANDLE destinationPtr =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();

    _rtvs.resize(_bufferNum);

    for (int i = 0; i < _bufferNum; i++)
    {
        if (FAILED(SetBufferToRTV(i)))
        {
            assert(false); return E_FAIL;
        }

        _device->CreateRenderTargetView(
            _rtvs[i].Get(),
            nullptr,
            destinationPtr);

        // RTVビューを入れた分、アドレスを足す
        destinationPtr.ptr +=
            _device->GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    return S_OK;
}

// 各RTVにバッファを対応させる
HRESULT DX12::SetBufferToRTV(UINT i)
{
    return _draw->SetBufferToRTV(
        i, _rtvs[i].ReleaseAndGetAddressOf());

}

// 頂点集合作成
HRESULT DX12::CreateVertexSets()
{
    int vertexNum = 1;
    _vertices.resize(vertexNum);

    std::for_each(_vertices.begin(), _vertices.end(),
        [](std::shared_ptr<Vertex>& vertex)
        {
            vertex.reset(new Vertex);
        });

    return S_OK;
}

// 頂点バッファ作成
HRESULT DX12::CreateVertexBuffer()
{
    // 頂点ヒーププロパティ取得
    D3D12_HEAP_PROPERTIES heapProperty =
        GetHeapProperty();
    // リソースディスクリプタ取得
    D3D12_RESOURCE_DESC resourceDesc =
        GetResourceDesc();

    return _device->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(_vertexBuffer.ReleaseAndGetAddressOf()));

}

D3D12_HEAP_PROPERTIES DX12::GetHeapProperty()
{
    D3D12_HEAP_PROPERTIES prop = {};

    prop.Type =
        D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty =
        D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference =
        D3D12_MEMORY_POOL_UNKNOWN;

    return prop;
}

D3D12_RESOURCE_DESC DX12::GetResourceDesc()
{
    D3D12_RESOURCE_DESC desc = {};

    desc.Dimension =
        D3D12_RESOURCE_DIMENSION_BUFFER;
    auto size = _vertices[0]->GetVerticesPtr().size();
    desc.Width =
        _vertices[0]->GetVerticesPtr().size() * sizeof(DirectX::XMFLOAT3);
    desc.Height =
        1;
    desc.DepthOrArraySize =
        1;
    desc.MipLevels =
        1;
    desc.Format =
        DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count =
        1;
    desc.Flags =
        D3D12_RESOURCE_FLAG_NONE;
    desc.Layout =
        D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    return desc;
}

// バッファに頂点をマップ
HRESULT DX12::MapVertexToBuffer()
{
    DirectX::XMFLOAT3* vertexMap;

    HRESULT result = _vertexBuffer->Map(
        0, nullptr, (void**)&vertexMap);
    if (FAILED(result))
    {
        assert(false); return E_FAIL;
    }

    auto vertices = _vertices[0]->GetVerticesPtr();

    std::copy(vertices.begin(), vertices.end(), vertexMap);

    _vertexBuffer->Unmap(0, nullptr);
    

    return S_OK;
}







// コマンド実行
void DX12::ExecuteDX12()
{
    // 現在のバックバッファのインデックス、ハンドルを取得
    auto backBufferIdx = GetBackBufferIdx();
    auto rtvHandle = GetRTVHandle(backBufferIdx);

    // バックバッファに対応するRTVのリソースをレンダーターゲットに設定
    ChangeRTVBarrierToRenderTarget(_rtvs[backBufferIdx].Get());
    SetRenderTarget(rtvHandle);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);

    // 頂点バッファのセット
    // SetVertexBuffer();

    // RTVを表示画面リソースに設定
    ChangeRTVBarrierToPresent(_rtvs[backBufferIdx].Get());

    // 描画実行
    ExecuteDraw();
    
    // 画面スワップ
    DisplaySwap();

    return;
}


UINT DX12::GetBackBufferIdx(){return _draw->GetBackBufferIdx();}

D3D12_CPU_DESCRIPTOR_HANDLE DX12::GetRTVHandle(UINT idx)
{
    auto handle =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    auto offset =
        _device->GetDescriptorHandleIncrementSize(
              D3D12_DESCRIPTOR_HEAP_TYPE_RTV); 
    handle.ptr += idx * offset;

    return handle;
}

// 描画実行
void DX12::ExecuteDraw()
{
     // コマンド実行および同期処理
    CloseCommand();
    ExecuteCommand();
    WaitProcessWithFence();
    ResetCommand();
}

// 頂点バッファをコマンドリストへセット
void DX12::SetVertexBuffer()
{
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView =
        GetVertexBufferView();

    //_draw->SetVertexBuffer(vertexBufferView);
}

D3D12_VERTEX_BUFFER_VIEW DX12::GetVertexBufferView()
{
    D3D12_VERTEX_BUFFER_VIEW view;

    auto vertexSize    = sizeof(DirectX::XMFLOAT3);
    auto allVertexSize = vertexSize * _vertices[0]->GetVerticesPtr().size();

    view.BufferLocation =
        _vertexBuffer->GetGPUVirtualAddress();
    view.SizeInBytes =
        allVertexSize;
    view.StrideInBytes =
        vertexSize;

    return view;
}


void DX12::ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv){_draw->ChangeRTVBarrierToRenderTarget(rtv);}
void DX12::ChangeRTVBarrierToPresent     (ID3D12Resource* rtv){_draw->ChangeRTVBarrierToPresent     (rtv);}

void DX12::SetRenderTarget  (D3D12_CPU_DESCRIPTOR_HANDLE handle){_draw->SetRenderTarget  (handle);}
void DX12::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle){_draw->ClearRenderTarget(handle);}

void DX12::CloseCommand()  {_draw->CloseCommand();  }
void DX12::ExecuteCommand(){_draw->ExecuteCommand();}
void DX12::ResetCommand()  {_draw->ResetCommand();  }

void DX12::WaitProcessWithFence(){_draw->WaitProcessWithFence();}
void DX12::DisplaySwap(){_draw->DisplaySwap();}




DX12::DX12(HWND hwnd)
{
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _hwnd = hwnd;
}