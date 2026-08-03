#include"Pawn.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Pawn::GetMovementBits()
{
    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetTopBit(); // 上

    return movementBits;
}

Pawn::Pawn(PlayerSide playerSide) : I_Piece(215.0f, 260.0f, GameObjType::PAWN, playerSide){}