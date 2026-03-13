#include"ConstBuff.h"

ID3D12Resource* ConstBuff::GetBuff(){return _constBuff.Get();} // コンスタントバッファを返す

ConstBuff::ConstBuff(){}
ConstBuff::~ConstBuff(){}