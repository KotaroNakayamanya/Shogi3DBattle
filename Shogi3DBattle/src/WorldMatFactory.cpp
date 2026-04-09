#include"WorldMatFactory.h"
#include"WorldMat.h"

// ƒ[ƒ‹ƒhs—ñì¬
std::unique_ptr<WorldMat> WorldMatFactory::CreateWorldMat()
{
    DirectX::XMMATRIX worldMat;
    worldMat = DirectX::XMMatrixIdentity();

    std::unique_ptr<WorldMat> uniquePtr = std::make_unique<WorldMat>();
    uniquePtr->SetMat(worldMat);

    return uniquePtr;
}