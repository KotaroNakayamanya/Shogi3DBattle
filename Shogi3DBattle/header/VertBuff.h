#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

#include"VertexStruct.h"

class VertBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _vertBuff; // 頂点バッファ

    D3D12_HEAP_PROPERTIES GetHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc(UINT byteSize);  // リソースディスクリプタ

public:
    HRESULT CreateVertBuff(ID3D12Device* device, UINT byteSize); // 頂点バッファ作成
    HRESULT WriteVertBuff(std::vector<VertexStruct::Vertex> vertexPtr); // 頂点バッファに書き込み
    ID3D12Resource* GetVertBuff(); // 頂点バッファを返す

    VertBuff();
    ~VertBuff();
};