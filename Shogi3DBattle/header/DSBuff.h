#pragma once

#include<d3d12.h>
#include<wrl.h>

class DSBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _dsBuff; // デプスステンシルバッファ
    
    D3D12_HEAP_PROPERTIES GetHeapProp(); // テクスチャヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc( // リソースディスクリプタ
        UINT windowWidth, UINT windowHeight);   
    DXGI_SAMPLE_DESC GetSampleDesc(); // サンプルディスクリプタ
    D3D12_CLEAR_VALUE GetClearValue(); // クリアバリュー

public:
    HRESULT CreateDSBuffObj( // デプスステンシルオブジェクト作成
        ID3D12Device* device, UINT windowWidth, UINT windowHeight);

    ID3D12Resource* GetDSBuff(); // デプスステンシルバッファを返す

    DSBuff();
    ~DSBuff();
};