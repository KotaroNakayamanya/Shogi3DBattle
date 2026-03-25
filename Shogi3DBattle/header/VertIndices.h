#pragma once

#include"BuffAddress.h"
#include<memory>
#include<vector>

class VertIndices : public BuffAddress
{
private:
    std::vector<USHORT> _vertIndices; // 頂点インデックス集合
    std::unique_ptr<BuffAddress> _buffAddress; // バッファアドレス

public:
    UINT GetVertIndicesSize();     // 頂点インデックスサイズを返す
    UINT GetVertIdxByteSize();     // 頂点インデックス1つ分のバイトサイズを返す
    UINT GetVertIndicesByteSize(); // 頂点インデックス全体のバイトサイズを返す

    void SetVertIndices(std::vector<USHORT> vertIndices); // 頂点インデックスセット
    std::vector<USHORT> GetVertIndices(); // 頂点インデックスを返す
    void SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress); // バッファアドレスセット
    D3D12_GPU_VIRTUAL_ADDRESS GetBuffAddress();              // バッファアドレスを返す

    VertIndices();
    ~VertIndices();
};