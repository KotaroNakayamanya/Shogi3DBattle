#pragma once

#include"I_PieceFactory.h"

class PawnFactory : public I_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ï‡Å@çÏê¨ 
};