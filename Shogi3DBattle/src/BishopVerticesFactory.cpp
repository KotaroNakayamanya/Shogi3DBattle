#include"BishopVerticesFactory.h"

// äpÅ@í∏ì_èWçáçÏê¨
std::unique_ptr<Vertices> BishopVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}