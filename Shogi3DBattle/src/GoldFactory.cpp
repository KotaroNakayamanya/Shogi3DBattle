#include"GoldFactory.h"
#include"Gold.h"

// ‹à@ì¬
std::unique_ptr<I_Piece> GoldFactory::CreatePiece()
{
    return std::make_unique<Gold>();
}