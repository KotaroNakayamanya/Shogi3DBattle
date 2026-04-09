#include"KingVerticesFactory.h"

// â§Å@í∏ì_èWçáçÏê¨
std::unique_ptr<Vertices> KingVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 285.0f;
    float mmHeight       = 320.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}