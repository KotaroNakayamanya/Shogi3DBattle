#pragma once

#include<d3d12.h>
#include<wrl.h>

class ConstBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _constBuff; // コンスタントバッファ

    D3D12_HEAP_PROPERTIES GetHeapProp(); // ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc(UINT verticesBytesSize); // リソースディスクリプタ

public:
    HRESULT CreateCBuffObj(ID3D12Device* device, UINT verticesByte); // コンスタントオブジェクト作成
    ID3D12Resource* GetBuff(); // バッファを返す

    ConstBuff();
    ~ConstBuff();
};