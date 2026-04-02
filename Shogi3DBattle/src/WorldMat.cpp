#include"WorldMat.h"

void WorldMat::SetWorldMat(DirectX::XMMATRIX worldMat){_worldMat = worldMat;} // ワールド行列セット
DirectX::XMMATRIX WorldMat::GetMat()                  {return _worldMat;}     // ワールド行列を返す