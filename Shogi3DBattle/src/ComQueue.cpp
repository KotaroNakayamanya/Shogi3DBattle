#include"ComQueue.h"

// コマンドキューを返す
ID3D12CommandQueue* ComQueue::GetComQueue(){return _comQueue.Get();}

ComQueue::ComQueue(){}
ComQueue::~ComQueue(){}