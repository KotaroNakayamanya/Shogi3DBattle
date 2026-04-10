#include"BishopFactory.h"
#include"Bishop.h"

// Šp@ì¬
std::unique_ptr<I_Piece> BishopFactory::CreatePiece()
{
    return std::make_unique<Bishop>();
}