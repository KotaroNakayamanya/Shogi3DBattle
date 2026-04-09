#pragma once

#include"B_PieceFactory.h"

class KingFactory : public B_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // â§Å@çÏê¨ 
};