#include"TexBuff.h"

ID3D12Resource* TexBuff::GetTexBuff(){return _texBuff.Get();} // バッファを渡す

TexBuff::TexBuff(){}
TexBuff::~TexBuff(){}