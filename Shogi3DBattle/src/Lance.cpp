#include"Lance.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Lance::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetTopBit();        // 上
    movementBits += PieceMovementBit::GetStraightVHBit(); // 縦横直進

    return movementBits;
}

Lance::Lance(PlayerSide playerSide) : I_Piece(225.0f, 280.0f, GameObjType::LANCE, playerSide){}