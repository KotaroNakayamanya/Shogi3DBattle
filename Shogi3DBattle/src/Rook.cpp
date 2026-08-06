#include"Rook.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Rook::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetStraightDownBit();  // 下
    movementBits += PieceMovementBit::GetStraightLeftBit();  // 左
    movementBits += PieceMovementBit::GetStraightRightBit(); // 右
    movementBits += PieceMovementBit::GetStraightUpBit();    // 上

    // 成っていたら斜めの動きを追加
    if (GetIsPromotion())
    {
        movementBits |= PieceMovementBit::GetLeftDownBit();  // 左下
        movementBits |= PieceMovementBit::GetRightDownBit(); // 右下
        movementBits |= PieceMovementBit::GetLeftUpBit();    // 左上
        movementBits |= PieceMovementBit::GetRightUpBit();   // 右上
    }

    return movementBits;
}

Rook::Rook(PlayerSide playerSide) : I_Piece(260.0f, 300.0f, GameObjType::ROOK, playerSide){}