#include"CmdQueue.h"

// コマンドキューを返す
ID3D12CommandQueue* CmdQueue::GetCmdQueue(){return _cmdQueue.Get();}

CmdQueue::CmdQueue(){}
CmdQueue::~CmdQueue(){}