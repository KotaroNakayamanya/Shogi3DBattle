#include"Pawn.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Pawn::GetMovementBits()
{
    // 成っていたら金の移動範囲を返す
    if(GetIsPromotion()) return PieceMovementBit::GetGoldMovementBits();

    unsigned short movementBits = 0;
    movementBits += PieceMovementBit::GetUpBit(); // 上

    return movementBits;
}

Pawn::Pawn(PlayerSide playerSide) : I_Piece(215.0f, 260.0f, GameObjType::PAWN, playerSide){}