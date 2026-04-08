#include"KnightVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// åjÅ@í∏ì_èWçáçÏê¨
std::unique_ptr<BufferedData> KnightVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 235.0f;
    float mmHeight       = 275.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::KNIGHT));

    return uniquePtr;
}