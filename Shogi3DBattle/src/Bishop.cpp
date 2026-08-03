#include"Bishop.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Bishop::GetMovementBits()
{
    unsigned short movementBits = 0;
    movementBits |= PieceMovementBit::GetLeftBottomBit();  // 左下
    movementBits |= PieceMovementBit::GetRightBottomBit(); // 右下

    movementBits |= PieceMovementBit::GetLeftTopBit();     // 左上
    movementBits |= PieceMovementBit::GetRightTopBit();    // 右上

    movementBits |= PieceMovementBit::GetStraightDBit();   // 斜め直進 

    return movementBits;
}

Bishop::Bishop(PlayerSide playerSide) : I_Piece(260.0f, 300.0f, GameObjType::BISHOP, playerSide){}