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

    return movementBits;
}

Rook::Rook(PlayerSide playerSide) : I_Piece(260.0f, 300.0f, GameObjType::ROOK, playerSide){}