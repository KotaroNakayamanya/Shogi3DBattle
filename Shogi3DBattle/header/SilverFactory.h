#pragma once

#include"I_PieceFactory.h"

class SilverFactory : public I_PieceFactory
{
public:
    std::unique_ptr<I_Piece> CreatePiece() override; // ã‚Å@çÏê¨ 
};