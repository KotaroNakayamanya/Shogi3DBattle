#include"KnightVerticesFactory.h"

// Œj@’¸“_W‡ì¬
std::unique_ptr<Vertices> KnightVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 235.0f;
    float mmHeight       = 275.0f;
 
    return CreatePieceVertices(mmBottomWidth, mmHeight);
}