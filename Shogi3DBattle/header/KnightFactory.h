#pragma once

#include"B_PieceFactory.h"

class KnightFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // Œj@ì¬ 
};