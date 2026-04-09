#pragma once

#include"B_PieceFactory.h"

class PawnFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ï‡Å@çÏê¨ 
};