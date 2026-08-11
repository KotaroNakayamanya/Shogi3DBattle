#pragma once

#include"I_Piece.h"

class Gold : public I_Piece
{
public:
    unsigned int GetMovementBits() override; // 移動出来る範囲をビット列で返す

    Gold(PlayerSide playerSide);
};