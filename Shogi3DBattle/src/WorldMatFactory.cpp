#include"WorldMatFactory.h"
#include"WorldMat.h"
#include"FactoryMethod.h"

// ワールド行列作成
std::unique_ptr<I_BufferedData> WorldMatFactory::CreateUniquePtr()
{
    DirectX::XMMATRIX worldMat;
    worldMat = DirectX::XMMatrixIdentity();

    std::unique_ptr<WorldMat> uniquePtr = std::make_unique<WorldMat>();
    uniquePtr->SetMat(worldMat);

    return uniquePtr;
}

// ワールド行列作成
std::unique_ptr<I_WorldMat> WorldMatFactory::CreateWorldMat()
{
    DirectX::XMMATRIX worldMat;
    worldMat = DirectX::XMMatrixIdentity();

    std::unique_ptr<WorldMat> uniquePtr = std::make_unique<WorldMat>();
    uniquePtr->SetMat(worldMat);

    return uniquePtr;
}