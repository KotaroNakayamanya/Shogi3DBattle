#include"Rook.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Rook::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetBottomBit();     // 下
    movementBits += PieceMovementBit::GetLeftBit();       // 左
    movementBits += PieceMovementBit::GetRightBit();      // 右
    movementBits += PieceMovementBit::GetTopBit();        // 上

    movementBits += PieceMovementBit::GetStraightVHBit(); // 縦横直進

    // 成っていたら縦横の動きを追加
    if (GetIsPromotion())
    {
        movementBits |= PieceMovementBit::GetLeftBottomBit();  // 左下
        movementBits |= PieceMovementBit::GetRightBottomBit(); // 右下
        movementBits |= PieceMovementBit::GetLeftTopBit();     // 左上
        movementBits |= PieceMovementBit::GetRightTopBit();    // 右上
    }

    return movementBits;
}

Rook::Rook(PlayerSide playerSide) : I_Piece(260.0f, 300.0f, GameObjType::ROOK, playerSide){}