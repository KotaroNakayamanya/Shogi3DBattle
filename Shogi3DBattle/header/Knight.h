#pragma once

#include"I_Piece.h"

class Knight : public I_Piece
{
public:
    unsigned short GetMovementBits() override; // 移動出来る範囲をビット列で返す

    Knight(PlayerSide playerSide);
};