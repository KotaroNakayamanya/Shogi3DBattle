#include"King.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short King::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetLeftBottomBit();  // 左下
    movementBits += PieceMovementBit::GetBottomBit();      // 左下
    movementBits += PieceMovementBit::GetRightBottomBit(); // 右下

    movementBits += PieceMovementBit::GetLeftBit();        // 左
    movementBits += PieceMovementBit::GetRightBit();       // 右

    movementBits += PieceMovementBit::GetLeftTopBit();     // 左上
    movementBits += PieceMovementBit::GetTopBit();         // 上
    movementBits += PieceMovementBit::GetRightTopBit();    // 右上

    return movementBits;
;
}

King::King(PlayerSide playerSide) : I_Piece(285.0f, 320.0f, GameObjType::KING, playerSide){}