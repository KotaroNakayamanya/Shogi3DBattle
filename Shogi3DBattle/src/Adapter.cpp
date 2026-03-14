#include"Adapter.h"

// 使用するアダプターを渡す
IDXGIAdapter* Adapter::GetAdapter(){return _adapter.Get();}

Adapter::Adapter(){}
Adapter::~Adapter(){}