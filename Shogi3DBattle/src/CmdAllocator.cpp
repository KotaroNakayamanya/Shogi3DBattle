#include"CmdAllocator.h"

// コマンドリセット
void CmdAllocator::Reset()
{
    _cmdAllocator->Reset();
}

// コマンドアロケータセット
void CmdAllocator::SetCmdAllocator(ComPtr<ID3D12CommandAllocator> cmdAllocator){_cmdAllocator = cmdAllocator;}
// コマンドアロケータを返す
ID3D12CommandAllocator* CmdAllocator::GetCmdAllocator(){return _cmdAllocator.Get();}

CmdAllocator::CmdAllocator(){}
CmdAllocator::~CmdAllocator(){}