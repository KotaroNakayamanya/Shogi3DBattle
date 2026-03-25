#include"BufferedData.h"

// バッファアドレスセット
void BufferedData::SetBuffAddress (D3D12_GPU_VIRTUAL_ADDRESS buffAddress){_buffAddress = buffAddress;}
// バッファアドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS BufferedData::GetBuffAddress(){return _buffAddress;}

BufferedData::BufferedData(){}
BufferedData::~BufferedData(){}