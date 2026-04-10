#include"KingFactory.h"
#include"King.h"

// ‰¤@ì¬
std::unique_ptr<I_Piece> KingFactory::CreatePiece()
{
    return std::make_unique<King>();
}