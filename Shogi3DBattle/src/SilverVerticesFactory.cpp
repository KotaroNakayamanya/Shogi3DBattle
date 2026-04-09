#include"SilverVerticesFactory.h"

// ã‚Å@í∏ì_èWçáçÏê¨
std::unique_ptr<Vertices> SilverVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 250.0f;
    float mmHeight       = 285.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}