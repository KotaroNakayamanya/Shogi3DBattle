#include"KnightFactory.h"
#include"Knight.h"

// Œj@ì¬
std::unique_ptr<I_Piece> KnightFactory::CreatePiece()
{
    return std::make_unique<Knight>();
}