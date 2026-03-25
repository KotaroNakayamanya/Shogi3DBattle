#include"Buff.h"

// リソースディスクリプタを返す
D3D12_RESOURCE_DESC Buff::GetResourceDesc()
{
    return _buff->GetDesc();
}

// バッファセット
void Buff::SetBuff(ComPtr<ID3D12Resource> buff){_buff = buff;}
// バックバッファを返す
ID3D12Resource* Buff::GetBuff(){return _buff.Get();}

Buff::Buff(){}
Buff::~Buff(){}