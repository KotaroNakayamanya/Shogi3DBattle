#include"GoldFactory.h"
#include"Gold.h"
#include"GoldVerticesFactory.h"
#include"WorldMatFactory.h"

// 金　作成
std::unique_ptr<I_Piece> GoldFactory::CreatePiece()
{
    std::unique_ptr<Gold> uniquePtr = std::make_unique<Gold>();

    // 頂点集合作成
    _verticesFactory.reset(new GoldVerticesFactory());
    auto kingVerticesUniquePtr = _verticesFactory->CreateVertices();
    auto kingVerticesPtr = kingVerticesUniquePtr.get();
    kingVerticesUniquePtr.release();
    uniquePtr->SetVertices(kingVerticesPtr);

    // ワールド行列作成
    _worldMatFactory.reset(new WorldMatFactory());
    auto worldMatUniquePtr = _worldMatFactory->CreateWorldMat();
    auto worldMatPtr = worldMatUniquePtr.get();
    worldMatUniquePtr.release();
    uniquePtr->SetWorldMat(worldMatPtr);

    return uniquePtr;
}