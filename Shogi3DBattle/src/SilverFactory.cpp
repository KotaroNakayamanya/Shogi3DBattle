#include"SilverFactory.h"
#include"Silver.h"

// ‹â@ì¬
std::unique_ptr<I_Piece> SilverFactory::CreatePiece()
{
    return std::make_unique<Silver>();
}