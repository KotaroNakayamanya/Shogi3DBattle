#include"PawnVerticesFactory.h"

// ï‡Å@í∏ì_èWçáçÏê¨
std::unique_ptr<Vertices> PawnVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 215.0f;
    float mmHeight       = 260.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}