#include"KingFactory.h"
#include"King.h"
#include"KingVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

// 王　作成
std::unique_ptr<I_GameObj> KingFactory::CreateUniquePtr()
{
    std::unique_ptr<King> uniquePtr = std::make_unique<King>();

    // 頂点集合作成
    _verticesFactory.reset(new KingVerticesFactory());
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