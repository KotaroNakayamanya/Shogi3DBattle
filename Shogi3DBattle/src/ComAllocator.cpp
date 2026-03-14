#include"ComAllocator.h"

// コマンドアロケータを返す
ID3D12CommandAllocator* ComAllocator::GetCommandAllocator(){return _comAllocator.Get();}

ComAllocator::ComAllocator(){}
ComAllocator::~ComAllocator(){}