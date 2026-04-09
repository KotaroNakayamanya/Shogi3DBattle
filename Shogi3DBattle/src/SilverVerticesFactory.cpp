#include"SilverVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// ã‚Å@í∏ì_èWçáçÏê¨
std::unique_ptr<I_Vertices> SilverVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 250.0f;
    float mmHeight       = 285.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}