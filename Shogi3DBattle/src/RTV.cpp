#include"RTV.h"

ID3D12Resource* RTV::GetRTV(){return _rtv.Get();} // RTV‚ð•Ô‚·
D3D12_CPU_DESCRIPTOR_HANDLE RTV::GetRTVHandle(){return _rtvHandle;} // RTVƒnƒ“ƒhƒ‹‚ð•Ô‚·

RTV::RTV(){}
RTV::~RTV(){}