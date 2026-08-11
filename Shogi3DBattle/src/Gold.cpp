#include"Gold.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned int Gold::GetMovementBits()
{
    return PieceMovementBit::GetGoldMovementBits();
}

Gold::Gold(PlayerSide playerSide) : I_Piece(250.0f, 285.0f, GameObjType::GOLD, playerSide){}