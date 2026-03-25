#include"VertIndices.h"

// 頂点インデックスサイズを返す
UINT VertIndices::GetVertIndicesSize()
{
    return static_cast<UINT>(_vertIndices.size());
}
// 頂点インデックス1つ分のバイトサイズを返す
UINT VertIndices::GetVertIdxByteSize()
{
    return sizeof(_vertIndices[0]);
}
// 頂点インデックス全体のバイトサイズを返す
UINT VertIndices::GetVertIndicesByteSize()
{
    return GetVertIdxByteSize() * GetVertIndicesSize();
}

// 頂点インデックスセット
void VertIndices::SetVertIndices(std::vector<USHORT> vertIndices){_vertIndices = vertIndices;}
// 頂点インデックスを返す
std::vector<USHORT> VertIndices::GetVertIndices(){return _vertIndices;}
// バッファアドレスセット
void VertIndices::SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress){_buffAddress->SetBuffAddress(buffAddress);}
// バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS VertIndices::GetBuffAddress(){return _buffAddress->GetBuffAddress();}

VertIndices::VertIndices()
{
    _buffAddress = std::make_unique<BuffAddress>();
}
VertIndices::~VertIndices(){}