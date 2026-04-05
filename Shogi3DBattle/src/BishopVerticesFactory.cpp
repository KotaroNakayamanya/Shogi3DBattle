#include"BishopVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// äpÅ@í∏ì_èWçáçÏê¨
std::unique_ptr<BufferedData<Vert>> BishopVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::BISHOP));

    return uniquePtr;
}