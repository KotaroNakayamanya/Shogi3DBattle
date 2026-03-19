#include"CmdQueue.h"

// コマンド実行
void CmdQueue::ExeCmd(CmdList* cmdList)
{
    ID3D12CommandList* commandLists[] = {cmdList->GetCmdList()}; // リストに格納
    _cmdQueue->ExecuteCommandLists(1, commandLists); // コマンドキュー実行
}

// コマンドキューを返す
ID3D12CommandQueue* CmdQueue::GetCmdQueue(){return _cmdQueue.Get();}

CmdQueue::CmdQueue(){}
CmdQueue::~CmdQueue(){}