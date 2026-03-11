#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

class IdxBuff
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _idxBuff;  // インデックスバッファ

    D3D12_HEAP_PROPERTIES GetVertexHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetVertexResourceDesc(UINT byteSize);  // リソースディスクリプタ

public:
    HRESULT CreateIdxBuff(ID3D12Device* device, UINT byteSize); // インデックスバッファ作成
    HRESULT WriteIdxBuff(std::vector<unsigned short> indexPtr);  // インデックスに書き込み
    ID3D12Resource* GetIdxBuff(); // インデックスバッファを返す

    IdxBuff();
    ~IdxBuff();
};