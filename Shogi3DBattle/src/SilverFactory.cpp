#include"SilverFactory.h"
#include"Silver.h"
#include"SilverVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

// 銀　作成
std::unique_ptr<I_GameObj> SilverFactory::CreateUniquePtr()
{
    std::unique_ptr<Silver> uniquePtr = std::make_unique<Silver>();

    // 頂点集合作成
    _verticesFactory.reset(new SilverVerticesFactory());
    auto kingVerticesUniquePtr =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory>(_verticesFactory.get());
    auto kingVerticesPtr = kingVerticesUniquePtr.get();
    kingVerticesUniquePtr.release();
    uniquePtr->SetVertices(kingVerticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto worldMatUniquePtr = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory>(_matFactory.get());
    auto worldMatPtr = worldMatUniquePtr.get();
    worldMatUniquePtr.release();
    uniquePtr->SetWorldMat(worldMatPtr);

    return uniquePtr;
}