#include"WorldMat.h"

std::vector<DirectX::XMMATRIX> WorldMat::GetDatas(){return {GetMat()};} // データ集合を返す

void WorldMat::SetWorldMat(DirectX::XMMATRIX worldMat){_worldMat = worldMat;} // ワールド行列セット
DirectX::XMMATRIX WorldMat::GetMat()                  {return _worldMat;}     // ワールド行列を返す