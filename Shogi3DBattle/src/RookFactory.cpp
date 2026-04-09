#include"RookFactory.h"
#include"Rook.h"
#include"RookVerticesFactory.h"
#include"WorldMatFactory.h"

// 飛　作成
std::unique_ptr<I_Piece> RookFactory::CreatePiece()
{
    std::unique_ptr<Rook> uniquePtr = std::make_unique<Rook>();

    // 頂点集合作成
    _verticesFactory.reset(new RookVerticesFactory());
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