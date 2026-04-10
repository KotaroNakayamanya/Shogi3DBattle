#include"LanceFactory.h"
#include"Lance.h"

//@ @ì¬
std::unique_ptr<I_Piece> LanceFactory::CreatePiece()
{
    return std::make_unique<Lance>();
}