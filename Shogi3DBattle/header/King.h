#pragma once

#include"I_Piece.h"

class King : public I_Piece
{
public:
    unsigned int GetMovementBits() override; // 移動出来る範囲をビット列で返す

    King(PlayerSide playerSide);
};