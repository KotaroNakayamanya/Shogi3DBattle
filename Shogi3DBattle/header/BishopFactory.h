#pragma once

#include"B_PieceFactory.h"

class BishopFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // Šp@ì¬ 
};