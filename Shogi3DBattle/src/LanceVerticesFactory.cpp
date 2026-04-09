#include"LanceVerticesFactory.h"

// @’¸“_W‡ì¬
std::unique_ptr<Vertices> LanceVerticesFactory::CreateVertices()
{
    float mmBottomWidth  = 225.0f;
    float mmHeight       = 280.0f;

    return CreatePieceVertices(mmBottomWidth, mmHeight);
}