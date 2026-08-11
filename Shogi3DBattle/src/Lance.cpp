#include"Lance.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned int Lance::GetMovementBits()
{
    // 成っていたら金の移動範囲を返す
    if(GetIsPromotion()) return PieceMovementBit::GetGoldMovementBits();

    unsigned int movementBits = 0;
    movementBits |= PieceMovementBit::GetStraightUpBit(); // 上直進

    return movementBits;
}

Lance::Lance(PlayerSide playerSide) : I_Piece(225.0f, 280.0f, GameObjType::LANCE, playerSide){}