#include"ResourceBarrier.h"

// レンダーターゲット変更用リソースバリアを返す
D3D12_RESOURCE_BARRIER ResourceBarrier::GetRBToRenderTarget(ID3D12Resource* resource)
{
    D3D12_RESOURCE_BARRIER rb = 
        GetBasiceResourceBarrier();

    rb.Transition.pResource =
        resource;
    rb.Transition.StateBefore =
        D3D12_RESOURCE_STATE_PRESENT;
    rb.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_RENDER_TARGET;

    return rb;
}

// 画面表示変更用リソースバリアを返す
D3D12_RESOURCE_BARRIER ResourceBarrier::GetRBToPresent(ID3D12Resource* resource)
{
    D3D12_RESOURCE_BARRIER rb =
        GetBasiceResourceBarrier();

    rb.Transition.pResource =
        resource;
    rb.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    rb.Transition.StateAfter  =
        D3D12_RESOURCE_STATE_PRESENT;

    return rb;
}

// リソースバリア基本設定
D3D12_RESOURCE_BARRIER ResourceBarrier::GetBasiceResourceBarrier()
{
    D3D12_RESOURCE_BARRIER rb = {};

    rb.Type =
        D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    rb.Flags =
        D3D12_RESOURCE_BARRIER_FLAG_NONE;
    rb.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    return rb;
}

ResourceBarrier::ResourceBarrier(){}
ResourceBarrier::~ResourceBarrier(){}