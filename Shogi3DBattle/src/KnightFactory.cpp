#include"KnightFactory.h"
#include"Knight.h"
#include"KnightVerticesFactory.h"
#include"WorldMatFactory.h"

// 桂　作成
std::unique_ptr<I_Piece> KnightFactory::CreatePiece()
{
    std::unique_ptr<Knight> uniquePtr = std::make_unique<Knight>();

    // 頂点集合作成
    _verticesFactory.reset(new KnightVerticesFactory());
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