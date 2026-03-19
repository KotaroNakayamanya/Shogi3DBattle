#pragma once

#include<d3d12.h>

class ResourceBarrier
{
private:
    D3D12_RESOURCE_BARRIER GetBasiceResourceBarrier(); // リソースバリア基本設定

public:
    D3D12_RESOURCE_BARRIER GetRBToRenderTarget(ID3D12Resource* resource); // レンダーターゲット変更用リソースバリアを返す
    D3D12_RESOURCE_BARRIER GetRBToPresent     (ID3D12Resource* resource); // 画面表示変更用リソースバリアを返す

    ResourceBarrier();
    ~ResourceBarrier();
};