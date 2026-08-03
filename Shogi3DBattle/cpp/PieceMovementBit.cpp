#include"PieceMovementBit.h"

unsigned short PieceMovementBit::GetLeftBottomBit (){return 1 <<  0;} // 左下
unsigned short PieceMovementBit::GetBottomBit     (){return 1 <<  1;} // 下
unsigned short PieceMovementBit::GetRightBottomBit(){return 1 <<  2;} // 右下
unsigned short PieceMovementBit::GetLeftBit       (){return 1 <<  3;} // 左
unsigned short PieceMovementBit::GetRightBit      (){return 1 <<  4;} // 右
unsigned short PieceMovementBit::GetLeftTopBit    (){return 1 <<  5;} // 左上
unsigned short PieceMovementBit::GetTopBit        (){return 1 <<  6;} // 上
unsigned short PieceMovementBit::GetRightTopBit   (){return 1 <<  7;} // 右上
unsigned short PieceMovementBit::GetLeftTwoTopBit (){return 1 <<  8;} // 左上上
unsigned short PieceMovementBit::GetRightTwoTopBit(){return 1 <<  9;} // 右上上
unsigned short PieceMovementBit::GetStraightVHBit (){return 1 << 10;} // 縦横直進
unsigned short PieceMovementBit::GetStraightDBit  (){return 1 << 11;} // 斜め直進

// 金の動きのビット列
unsigned short PieceMovementBit::GetGoldMovementBits()
{
    unsigned short movementBits = 0;

    movementBits |= GetBottomBit();   // 下

    movementBits |= GetLeftBit();     // 左
    movementBits |= GetRightBit();    // 右

    movementBits |= GetLeftTopBit();  // 左上
    movementBits |= GetTopBit();      // 上
    movementBits |= GetRightTopBit(); // 右上

    return movementBits;
}
