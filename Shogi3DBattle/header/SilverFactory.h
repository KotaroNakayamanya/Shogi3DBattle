#pragma once

#include"B_PieceFactory.h"

class SilverFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ã‚Å@çÏê¨ 
};