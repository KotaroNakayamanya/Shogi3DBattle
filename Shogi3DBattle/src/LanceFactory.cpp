#include"LanceFactory.h"
#include"Lance.h"
#include"LanceVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"

//　香 　作成
std::unique_ptr<I_GameObj> LanceFactory::CreateUniquePtr()
{
    std::unique_ptr<Lance> uniquePtr = std::make_unique<Lance>();

    // 頂点集合作成
    _verticesFactory.reset(new LanceVerticesFactory());
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