#pragma once

#include"I_PieceFactory.h"

class BishopFactory : public I_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // Šp@ì¬ 
};