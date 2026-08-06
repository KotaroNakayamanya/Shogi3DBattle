#include"King.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short King::GetMovementBits()
{
    unsigned short movementBits = 0;
    movementBits += PieceMovementBit::GetDownBit();      // 左
    movementBits += PieceMovementBit::GetLeftBit();      // 左
    movementBits += PieceMovementBit::GetRightBit();     // 右
    movementBits += PieceMovementBit::GetUpBit();        // 上
    movementBits += PieceMovementBit::GetLeftDownBit();  // 左下
    movementBits += PieceMovementBit::GetRightDownBit(); // 右下
    movementBits += PieceMovementBit::GetLeftUpBit();    // 左上
    movementBits += PieceMovementBit::GetRightUpBit();   // 右上

    return movementBits;
;
}

King::King(PlayerSide playerSide) : I_Piece(285.0f, 320.0f, GameObjType::KING, playerSide){}