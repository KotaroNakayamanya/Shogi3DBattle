#include"SilverFactory.h"
#include"Silver.h"
#include"SilverVerticesFactory.h"
#include"WorldMatFactory.h"

// 銀　作成
std::unique_ptr<I_Piece> SilverFactory::CreatePiece()
{
    std::unique_ptr<Silver> uniquePtr = std::make_unique<Silver>();

    // 頂点集合作成
    _verticesFactory.reset(new SilverVerticesFactory());
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