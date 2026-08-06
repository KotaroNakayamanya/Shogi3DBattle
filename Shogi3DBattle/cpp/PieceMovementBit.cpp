#include"PieceMovementBit.h"

unsigned int PieceMovementBit::GetDownBit             (){return 1 <<  0;} // 下
unsigned int PieceMovementBit::GetLeftBit             (){return 1 <<  1;} // 左
unsigned int PieceMovementBit::GetRightBit            (){return 1 <<  2;} // 右
unsigned int PieceMovementBit::GetUpBit               (){return 1 <<  3;} // 上
unsigned int PieceMovementBit::GetLeftDownBit         (){return 1 <<  4;} // 左下
unsigned int PieceMovementBit::GetRightDownBit        (){return 1 <<  5;} // 右下
unsigned int PieceMovementBit::GetLeftUpBit           (){return 1 <<  6;} // 左上
unsigned int PieceMovementBit::GetRightUpBit          (){return 1 <<  7;} // 右上
unsigned int PieceMovementBit::GetStraightDownBit     (){return 1 <<  8;} // 下直進
unsigned int PieceMovementBit::GetStraightLeftBit     (){return 1 <<  9;} // 左直進
unsigned int PieceMovementBit::GetStraightRightBit    (){return 1 << 10;} // 右直進
unsigned int PieceMovementBit::GetStraightUpBit       (){return 1 << 11;} // 上直進
unsigned int PieceMovementBit::GetStraightLeftDownBit (){return 1 << 12;} // 左下直進
unsigned int PieceMovementBit::GetStraightRightDownBit(){return 1 << 13;} // 右下直進
unsigned int PieceMovementBit::GetStraightLeftUpBit   (){return 1 << 14;} // 左上直進
unsigned int PieceMovementBit::GetStraightRightUpBit  (){return 1 << 15;} // 右上直進
unsigned int PieceMovementBit::GetLeftDoubleUpBit     (){return 1 << 16;} // 左上上
unsigned int PieceMovementBit::GetRightDoubleUpBit    (){return 1 << 17;} // 右上上

// 金の動きのビット列
unsigned int PieceMovementBit::GetGoldMovementBits()
{
    unsigned int movementBits = 0;

    movementBits |= GetDownBit();    // 下
    movementBits |= GetLeftBit();    // 左
    movementBits |= GetRightBit();   // 右
    movementBits |= GetUpBit();      // 上
    movementBits |= GetLeftUpBit();  // 左上
    movementBits |= GetRightUpBit(); // 右上

    return movementBits;
}
