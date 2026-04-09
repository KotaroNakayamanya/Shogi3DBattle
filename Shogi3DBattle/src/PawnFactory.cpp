#include"PawnFactory.h"
#include"Pawn.h"
#include"PawnVerticesFactory.h"
#include"WorldMatFactory.h"

// 歩　作成
std::unique_ptr<I_Piece> PawnFactory::CreatePiece()
{
    std::unique_ptr<Pawn> uniquePtr = std::make_unique<Pawn>();

    // 頂点集合作成
    _verticesFactory.reset(new PawnVerticesFactory());
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