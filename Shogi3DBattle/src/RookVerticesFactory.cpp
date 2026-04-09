#include"RookVerticesFactory.h"

// ”ò@’¸“_W‡ì¬
std::unique_ptr<Vertices> RookVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 260.0f;
    float mmHeight       = 300.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}