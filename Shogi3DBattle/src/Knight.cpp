#include"Knight.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Knight::GetMovementBits()
{
    // 成っていたら金の移動範囲を返す
    if(GetIsPromotion()) return PieceMovementBit::GetGoldMovementBits();

    unsigned short movementBits = 0;
    movementBits += PieceMovementBit::GetLeftDoubleUpBit();  // 左上上
    movementBits += PieceMovementBit::GetRightDoubleUpBit(); // 右上上

    return movementBits;
}

Knight::Knight(PlayerSide playerSide) : I_Piece(235.0f, 275.0f, GameObjType::KNIGHT, playerSide){}