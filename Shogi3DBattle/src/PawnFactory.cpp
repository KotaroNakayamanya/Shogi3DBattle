#include"PawnFactory.h"
#include"Pawn.h"

// ï‡Å@çÏê¨
std::unique_ptr<I_Piece> PawnFactory::CreatePiece()
{
    return std::make_unique<Pawn>();
}