#pragma once

#include"I_Piece.h"
#include<memory>

class I_PieceFactory
{
public:
    virtual std::unique_ptr<I_Piece> CreatePiece() = 0; // ‹îì¬
    
    virtual ~I_PieceFactory() = default;
};