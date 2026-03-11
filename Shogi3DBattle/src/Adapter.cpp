#include"Adapter.h"

// 使用するアダプタをセットする
void Adapter::SetAdapterComPtr(ComPtr<IDXGIAdapter> adapter)
{
    _adapter = adapter;
}

// 使用するアダプターを渡す
IDXGIAdapter* Adapter::GetAdapter()
{
    return _adapter.Get();
}

Adapter::Adapter(){}
Adapter::~Adapter(){}