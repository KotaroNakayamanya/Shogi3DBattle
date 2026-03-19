#include"CmdAllocator.h"

// コマンドリセット
void CmdAllocator::Reset()
{
    _cmdAllocator->Reset();
}

// コマンドアロケータを返す
ID3D12CommandAllocator* CmdAllocator::GetCmdAllocator(){return _cmdAllocator.Get();}

CmdAllocator::CmdAllocator(){}
CmdAllocator::~CmdAllocator(){}