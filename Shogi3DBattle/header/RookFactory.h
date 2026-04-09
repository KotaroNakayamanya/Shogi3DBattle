#pragma once

#include"I_PieceFactory.h"

class RookFactory : public I_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ”ò@ì¬ 
};