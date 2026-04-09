#include"SilverVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// ã‚Å@í∏ì_èWçáçÏê¨
std::unique_ptr<I_BufferedData> SilverVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 250.0f;
    float mmHeight       = 285.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::SILVER));

    return uniquePtr;
}