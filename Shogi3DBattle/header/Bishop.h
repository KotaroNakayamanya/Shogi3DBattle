#pragma once

#include"I_Piece.h"

class Bishop : public I_Piece
{
public:
    unsigned int GetMovementBits() override; // 移動出来る範囲をビット列で返す

    Bishop(PlayerSide playerSide);
};