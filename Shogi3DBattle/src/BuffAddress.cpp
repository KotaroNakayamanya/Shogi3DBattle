#include"BuffAddress.h"

// バッファアドレスセット
void BuffAddress::SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress){_buffAddress = buffAddress;}
// バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS BuffAddress::GetBuffAddress(){return _buffAddress;}

BuffAddress::BuffAddress(){}
BuffAddress::~BuffAddress(){}