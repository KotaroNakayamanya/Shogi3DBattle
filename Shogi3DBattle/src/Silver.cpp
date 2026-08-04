#include"Silver.h"
#include"PieceMovementBit.h"

// 移動出来る範囲をビット列で返す
unsigned short Silver::GetMovementBits()
{
    // 成っていたら金の移動範囲を返す
    if(GetIsPromotion()) return PieceMovementBit::GetGoldMovementBits();

    unsigned short movementBits = 0;

    movementBits += PieceMovementBit::GetLeftBottomBit();  // 左下
    movementBits += PieceMovementBit::GetRightBottomBit(); // 右下

    movementBits += PieceMovementBit::GetLeftTopBit();     // 左上
    movementBits += PieceMovementBit::GetTopBit();         // 上
    movementBits += PieceMovementBit::GetRightTopBit();    // 右上

    return movementBits;
}

Silver::Silver(PlayerSide playerSide) : I_Piece(250.0f, 285.0f, GameObjType::SILVER, playerSide){}