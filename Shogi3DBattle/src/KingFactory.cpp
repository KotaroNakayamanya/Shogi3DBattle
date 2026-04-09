#include"KingFactory.h"
#include"King.h"
#include"KingVerticesFactory.h"
#include"WorldMatFactory.h"

// 王　作成
std::unique_ptr<I_Piece> KingFactory::CreatePiece()
{
    std::unique_ptr<King> uniquePtr = std::make_unique<King>();

    // 頂点集合作成
    _verticesFactory.reset(new KingVerticesFactory());
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