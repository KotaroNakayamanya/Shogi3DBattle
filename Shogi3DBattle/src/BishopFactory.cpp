#include"BishopFactory.h"
#include"Bishop.h"
#include"BishopVerticesFactory.h"
#include"WorldMatFactory.h"

// 角　作成
std::unique_ptr<I_Piece> BishopFactory::CreatePiece()
{
    std::unique_ptr<Bishop> uniquePtr = std::make_unique<Bishop>();

    // 頂点集合作成
    _verticesFactory.reset(new BishopVerticesFactory());
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