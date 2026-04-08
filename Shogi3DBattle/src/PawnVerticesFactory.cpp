#include"PawnVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// ï‡Å@í∏ì_èWçáçÏê¨
std::unique_ptr<BufferedData> PawnVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 215.0f;
    float mmHeight       = 260.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::PAWN));

    return uniquePtr;
}