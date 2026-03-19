#include"Adapter.h"

// 使用するアダプターセット
void Adapter::SetAdapter(ComPtr<IDXGIAdapter> adapter){_adapter = adapter;}
// 使用するアダプターを返す
IDXGIAdapter* Adapter::GetAdapter(){return _adapter.Get();}

Adapter::Adapter(){}
Adapter::~Adapter(){}