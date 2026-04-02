#include"Buff.h"

D3D12_RESOURCE_DESC Buff::GetResourceDesc(){return _buff->GetDesc();} // リソースディスクリプタを返す

void            Buff::SetBuff(ComPtr<ID3D12Resource> buff){_buff = buff;}       // バッファセット
ID3D12Resource* Buff::GetBuff()                           {return _buff.Get();} // バックバッファを返す