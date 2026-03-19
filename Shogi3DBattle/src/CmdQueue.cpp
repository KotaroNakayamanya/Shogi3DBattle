#include"CmdQueue.h"

// コマンド実行
void CmdQueue::ExeCmd(CmdList* cmdList)
{
    ID3D12CommandList* commandLists[] = {cmdList->GetCmdList()}; // リストに格納
    _cmdQueue->ExecuteCommandLists(1, commandLists); // コマンドキュー実行
}

// コマンドキューセット
void CmdQueue::SetCmdQueue(ComPtr<ID3D12CommandQueue> cmdQueue){_cmdQueue = cmdQueue;}
// コマンドキューを返す
ID3D12CommandQueue* CmdQueue::GetCmdQueue(){return _cmdQueue.Get();}
// コマンドキューポインタを返す
ID3D12CommandQueue** CmdQueue::GetCmdQueuePtr(){return _cmdQueue.GetAddressOf();}

CmdQueue::CmdQueue(){}
CmdQueue::~CmdQueue(){}