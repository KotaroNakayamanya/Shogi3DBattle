#include"Bishop.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned int Bishop::GetMovementBits()
{
    unsigned int movementBits = 0;

    movementBits |= PieceMovementBit::GetStraightLeftDownBit();  // 左下直進 
    movementBits |= PieceMovementBit::GetStraightRightDownBit(); // 右下直進 
    movementBits |= PieceMovementBit::GetStraightLeftUpBit();    // 左上直進 
    movementBits |= PieceMovementBit::GetStraightRightUpBit();   // 右上直進 

    // 成っていたら縦横の動きを追加
    if (GetIsPromotion())
    {
        movementBits |= PieceMovementBit::GetDownBit();  // 下
        movementBits |= PieceMovementBit::GetLeftBit();  // 左
        movementBits |= PieceMovementBit::GetRightBit(); // 右
        movementBits |= PieceMovementBit::GetUpBit();    // 上
    }

    return movementBits;
}

Bishop::Bishop(PlayerSide playerSide) : I_Piece(260.0f, 300.0f, GameObjType::BISHOP, playerSide){}