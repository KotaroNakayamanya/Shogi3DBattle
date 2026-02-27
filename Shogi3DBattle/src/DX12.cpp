#include"DX12.h"
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
bool DX12::CreateDX12BasicObject()
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
    

    // コマンドアロケータ、リスト、キュー作成
    if (FAILED(CreateCommandAllocator()))
    {
        assert(false); return false;
    }
    if (FAILED(CreateCommandList()))
    {
        assert(false); return false;
    }
    if (FAILED(CreateCommandQueue()))
    {
        assert(false); return false;
    }

    // スワップチェーン作成
    if (FAILED(CreateSwapChain()))
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

    // フェンス作成
    if (FAILED(CreateFence()))
    {
        assert(false); return false;
    }

    return true;
}

// コマンド実行
void DX12::RunDX12()
{
    // 現在のバックバッファのインデックスを取得
    auto currentBufferIdx =
        _swapChain->GetCurrentBackBufferIndex();

    // 対応したRTVをレンダーターゲットに設定
    SetRTVToRenderTargetWithBarrier(currentBufferIdx);

    // レンダーターゲットハンドルを取得
    auto rtvHandle = GetRTVHandle(currentBufferIdx);
    
    // レンダーターゲット設定
    _commandList->OMSetRenderTargets(1, &rtvHandle, true, nullptr);

    // レンダーターゲットクリア
    float clearRTVColor[] =
        {1.0f, 1.0f, 0.0f, 1.0f};
    _commandList->ClearRenderTargetView(
        rtvHandle, clearRTVColor, 0, nullptr);

    // 表示画面に設定
    SetRTVToPresentWithBarrier(currentBufferIdx);

    _commandList->Close();

    // コマンド実行
    ExecuteCommand();

    // フェンスによる同期制御
    WaitProcessWithFence();

    // コマンドリセット
    CommandReset();
    
    // 画面スワップ
    _swapChain->Present(1, 0);

    return;
}



// DXGIファクトリー作成
HRESULT DX12::CreateFactory()
{
    HRESULT result;
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


// 使用されているアダプター（グラフィックボード等）を取得する
void DX12::CreateUsedAdapterLists()
{
    // アダプターが見つからなくなるまでループする
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

            return result == S_OK;
        });

    return result;
}

// コマンドアロケータ作成
HRESULT DX12::CreateCommandAllocator()
{
    return _device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(_commandAllocator.ReleaseAndGetAddressOf()));
}

// コマンドリスト作成
HRESULT DX12::CreateCommandList()
{
    return _device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        _commandAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(_commandList.ReleaseAndGetAddressOf()));
}

// コマンドキュー作成
HRESULT DX12::CreateCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC commandQueueDesc =
        GetCommandQueueDesc();

    return _device->CreateCommandQueue(
        &commandQueueDesc,
        IID_PPV_ARGS(_commandQueue.ReleaseAndGetAddressOf()));
}

// スワップチェーン作成
HRESULT DX12::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = GetSwapChainDesc();

    return _dxgiFactory->CreateSwapChainForHwnd(
        _commandQueue.Get(),
        _hwnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)_swapChain.ReleaseAndGetAddressOf());
}

// レンダーターゲットビューヒープ作成
HRESULT DX12::CreateRTVHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetRTVHeapDesc();

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_rtvHeap.ReleaseAndGetAddressOf()));
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

HRESULT DX12::SetBufferToRTV(int i)
{
    return _swapChain->GetBuffer(
        i, IID_PPV_ARGS(_rtvs[i].ReleaseAndGetAddressOf()));
}

// フェンス作成
HRESULT DX12::CreateFence()
{
    return _device->CreateFence(
        _fenceVal,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
}




// コマンドリストディスクリプタを返す
D3D12_COMMAND_QUEUE_DESC DX12::GetCommandQueueDesc()
{
    D3D12_COMMAND_QUEUE_DESC desc;
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

// スワップチェーンディスクリプタを返す
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

// RTVヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC DX12::GetRTVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
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


// フェンスによる同期制御
void DX12::WaitProcessWithFence()
{
    // GPU処理完了後のフェンスの値を設定
    _commandQueue->Signal(_fence.Get(), ++_fenceVal);

    while (_fence->GetCompletedValue() != _fenceVal)
    {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        _fence->SetEventOnCompletion(_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}




// レンダーターゲットハンドルを返す
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

// RTVをレンダーターゲットに設定
void DX12::SetRTVToRenderTargetWithBarrier(
    UINT idx)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(_rtvs[idx].Get());

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    _commandList->ResourceBarrier(
        _bufferNum - 1,
        &bufferBarrierDesc);
}

// RTVを表示画面に設定
void DX12::SetRTVToPresentWithBarrier(
    UINT idx)
{
    D3D12_RESOURCE_BARRIER bufferBarrierDesc =
        GetBufferBarrierDesc(_rtvs[idx].Get());

    bufferBarrierDesc.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    bufferBarrierDesc.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    _commandList->ResourceBarrier(
        _bufferNum - 1,
        &bufferBarrierDesc);
}

D3D12_RESOURCE_BARRIER DX12::GetBufferBarrierDesc(
    ID3D12Resource* rtv)
{
    D3D12_RESOURCE_BARRIER desc;

    desc.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    desc.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;

    desc.Transition.pResource =
        rtv;
    desc.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    return desc;  
}

void DX12::CommandReset()
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);
}

void DX12::ExecuteCommand()
{
    ID3D12CommandList* commandLists[] = {_commandList.Get()};
    _commandQueue->ExecuteCommandLists(1, commandLists);
}



DX12::DX12(){}

DX12::DX12(HWND hwnd)
{
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _hwnd = hwnd;
}