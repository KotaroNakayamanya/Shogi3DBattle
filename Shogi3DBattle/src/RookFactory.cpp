#include"RookFactory.h"
#include"Rook.h"

// ”ò@ì¬
std::unique_ptr<I_Piece> RookFactory::CreatePiece()
{
    return std::make_unique<Rook>();
}