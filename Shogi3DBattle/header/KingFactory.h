#pragma once

#include"I_PieceFactory.h"

class KingFactory : public I_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // â§Å@çÏê¨ 
};