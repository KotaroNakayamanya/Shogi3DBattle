#include"Board9x9Factory.h"
#include"Board9x9.h"
#include"Board9x9VerticesFactory.h"
#include"WorldMatFactory.h"

// 9x9将棋盤作成
std::unique_ptr<I_Board> Board9x9Factory::CreateBoard()
{
    std::unique_ptr<Board9x9> uniquePtr = std::make_unique<Board9x9>();

    // 9x9将棋盤頂点集合作成
    _verticesFactory.reset(new Board9x9VerticesFactory());
    auto verticesUniquePtr = _verticesFactory->CreateVertices();
    verticesUniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::BOARD_99));
    auto verticesPtr = verticesUniquePtr.get();
    verticesUniquePtr.release();
    uniquePtr->SetVertices(verticesPtr);

    // ワールド行列作成
    _worldMatFactory.reset(new WorldMatFactory());
    auto worldMatUniquePtr = _worldMatFactory->CreateWorldMat();
    auto worldMatPtr = worldMatUniquePtr.get();
    worldMatUniquePtr.release();
    uniquePtr->SetWorldMat(worldMatPtr);

    uniquePtr->SetGameObjType(GameObjType::BOARD_99);

    return uniquePtr;
}