#include"LanceVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// @’¸“_W‡ì¬
std::unique_ptr<I_BufferedData> LanceVerticesFactory::CreateUniquePtr()
{
    float mmBottomWidth  = 225.0f;
    float mmHeight       = 280.0f;

    auto uniquePtr = PieceFactoryMethod::GetPieceVerticesUniquePtr(mmBottomWidth, mmHeight);
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType::LANCE));

    return uniquePtr;
}