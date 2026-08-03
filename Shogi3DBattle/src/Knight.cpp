#include"Knight.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Knight::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetLeftTwoTopBit();  // 左上上
    movementBits += PieceMovementBit::GetRightTwoTopBit(); // 右上上

    return movementBits;
}

Knight::Knight(PlayerSide playerSide) : I_Piece(235.0f, 275.0f, GameObjType::KNIGHT, playerSide){}