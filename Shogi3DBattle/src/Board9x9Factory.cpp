#include"Board9x9Factory.h"
#include"Board9x9.h"
#include"Board9x9VerticesFactory.h"

// 9x9«Šû”Õì¬
std::unique_ptr<I_Board> Board9x9Factory::CreateBoard()
{
    std::unique_ptr<Board9x9> uniquePtr = std::make_unique<Board9x9>();

    // 9x9«Šû”Õ’¸“_W‡ì¬
    _verticesFactory.reset(new Board9x9VerticesFactory());
    auto verticesUniquePtr = _verticesFactory->CreateVertices();
    verticesUniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::BOARD_99));
    auto verticesPtr = verticesUniquePtr.get();
    verticesUniquePtr.release();
    uniquePtr->SetVertices(verticesPtr);

    return uniquePtr;
}