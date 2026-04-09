#pragma once

#include"B_PieceFactory.h"

class RookFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ”ò@ì¬ 
};