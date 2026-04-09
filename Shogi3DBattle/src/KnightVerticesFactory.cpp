#include"KnightVerticesFactory.h"
#include"PieceFactoryMethod.h"
#include"GameObjType.h"

// åjÅ@í∏ì_èWçáçÏê¨
std::unique_ptr<I_Vertices> KnightVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 235.0f;
    float mmHeight       = 275.0f;
 
    return CreatePieceVertices(mmBottomWidth, mmHeight);
}