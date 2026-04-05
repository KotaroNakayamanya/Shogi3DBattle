#include"KingVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// â§Å@í∏ì_èWçáçÏê¨
std::unique_ptr<BufferedData<Vert>> KingVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 285.0f;
    float mmHeight       = 320.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::KING));

    return uniquePtr;
}