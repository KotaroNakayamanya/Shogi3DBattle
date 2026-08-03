#pragma once

class PieceMovementBit
{
public:
    static unsigned short GetLeftBottomBit();  // 左下
    static unsigned short GetBottomBit();      // 下
    static unsigned short GetRightBottomBit(); // 右下

    static unsigned short GetLeftBit();        // 左
    static unsigned short GetRightBit();       // 右

    static unsigned short GetLeftTopBit();     // 左上
    static unsigned short GetTopBit();         // 上
    static unsigned short GetRightTopBit();    // 右上

    static unsigned short GetLeftTwoTopBit();  // 左上上
    static unsigned short GetRightTwoTopBit(); // 右上上

    static unsigned short GetStraightVHBit();  // 縦横直進
    static unsigned short GetStraightDBit();   // 斜め直進


    static unsigned short GetGoldMovementBits(); // 金の動きのビット列
};
