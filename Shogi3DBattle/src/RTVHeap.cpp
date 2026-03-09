#include"RTVHeap.h"
#include<cassert>

// ヒープ作成
HRESULT RTVHeap::CreateHeap(
    ID3D12Device* device,
    IDXGISwapChain4* swapChain,
    UINT buffNum)
{
    HRESULT result;

    // ヒープ作成
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetHeapDesc(buffNum);

    result = device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_heap.ReleaseAndGetAddressOf()));
    if (FAILED(result))
    {
        assert(false); return result;
    }

    // RTV作成
    CreateRTV(device, swapChain, buffNum);

    return result;
}
    
// RTV作成
HRESULT RTVHeap::CreateRTV(
    ID3D12Device* device,
    IDXGISwapChain4* swapChain,
    UINT buffNum)
{
    _rtvs.resize(buffNum);

    // ヒープの先頭アドレスを取得しておく
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle =
        _heap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < buffNum; i++)
    {
        if (FAILED(SetRTVBuffer(swapChain, i))) // 各RTVにバッファを対応させる
        {
            assert(false); return E_FAIL;
        }

        device->CreateRenderTargetView(
            _rtvs[i].Get(),
            nullptr,
            rtvHeapHandle);

        // RTVビューを入れた分、アドレスを足す
        rtvHeapHandle.ptr +=
            device->GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    return S_OK;
}

// RTVにバッファを対応させる
 HRESULT RTVHeap::SetRTVBuffer(
    IDXGISwapChain4* swapChain,
    UINT i)
{
    return swapChain->GetBuffer(
        i, 
        IID_PPV_ARGS(_rtvs[i].ReleaseAndGetAddressOf()));
}




// ヒープディスクリプタ
D3D12_DESCRIPTOR_HEAP_DESC RTVHeap::GetHeapDesc(UINT buffNum)
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        buffNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
}


// RTVを破棄する
void RTVHeap::ClearRTV()
{
    _rtvs.clear();
}

// ヒープを返す
ID3D12DescriptorHeap* RTVHeap::GetHeap()
{
    return _heap.Get();
}

// RTVを返す
ID3D12Resource* RTVHeap::GetRTV(UINT i)
{
    return _rtvs[i].Get();
}





RTVHeap::RTVHeap(){}
RTVHeap::~RTVHeap(){}