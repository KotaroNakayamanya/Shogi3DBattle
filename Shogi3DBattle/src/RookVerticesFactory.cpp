#include"RookVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// ”ò@’¸“_W‡ì¬
std::unique_ptr<BufferedData<Vert>> RookVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::ROOK));

    return uniquePtr;
}