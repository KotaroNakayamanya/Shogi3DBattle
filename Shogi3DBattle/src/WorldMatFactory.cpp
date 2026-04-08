#include"WorldMatFactory.h"
#include"WorldMat.h"
#include"FactoryMethod.h"

// ƒ[ƒ‹ƒhs—ñì¬
std::unique_ptr<BufferedData> WorldMatFactory::CreateUniquePtr()
{
    DirectX::XMMATRIX worldMat;
    worldMat = DirectX::XMMatrixIdentity();

    std::unique_ptr<WorldMat> uniquePtr = std::make_unique<WorldMat>();
    uniquePtr->SetWorldMat(worldMat);

    return uniquePtr;
}