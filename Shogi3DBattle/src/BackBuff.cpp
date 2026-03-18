#include"BackBuff.h"

ID3D12Resource* BackBuff::GetBackBuff(){return _backBuff.Get();} // バックバッファを返す
D3D12_CPU_DESCRIPTOR_HANDLE BackBuff::GetRTVHandle(){return _rtvHandle;} // RTVハンドルを返す

BackBuff::BackBuff(){}
BackBuff::~BackBuff(){}