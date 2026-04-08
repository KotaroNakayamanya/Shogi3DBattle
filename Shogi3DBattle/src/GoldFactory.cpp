#include"GoldFactory.h"
#include"Gold.h"
#include"GoldVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

// 金　作成
std::unique_ptr<I_GameObj> GoldFactory::CreateUniquePtr()
{
    std::unique_ptr<Gold> uniquePtr = std::make_unique<Gold>();

    // 頂点集合作成
    _verticesFactory.reset(new GoldVerticesFactory());
    auto kingVerticesUniquePtr =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory<Vert>>(_verticesFactory.get());
    auto kingVerticesPtr = kingVerticesUniquePtr.get();
    kingVerticesUniquePtr.release();
    uniquePtr->SetVertices(kingVerticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto worldMatUniquePtr = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory<DirectX::XMMATRIX>>(_matFactory.get());
    auto worldMatPtr = worldMatUniquePtr.get();
    worldMatUniquePtr.release();
    uniquePtr->SetWorldMat(worldMatPtr);

    return uniquePtr;
}