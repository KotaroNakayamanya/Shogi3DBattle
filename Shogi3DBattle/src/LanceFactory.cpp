#include"LanceFactory.h"
#include"Lance.h"
#include"LanceVerticesFactory.h"
#include"WorldMatFactory.h"

//　香 　作成
std::unique_ptr<I_Piece> LanceFactory::CreatePiece()
{
    std::unique_ptr<Lance> uniquePtr = std::make_unique<Lance>();

    // 頂点集合作成
    _verticesFactory.reset(new LanceVerticesFactory());
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