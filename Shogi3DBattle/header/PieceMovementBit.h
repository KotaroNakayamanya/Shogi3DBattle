#pragma once

class PieceMovementBit
{
public:
    static unsigned int GetDownBit();              // 下
    static unsigned int GetLeftBit();              // 左
    static unsigned int GetRightBit();             // 右
    static unsigned int GetUpBit();                // 上
    static unsigned int GetLeftDownBit();          // 左下
    static unsigned int GetRightDownBit();         // 右下
    static unsigned int GetLeftUpBit();            // 左上
    static unsigned int GetRightUpBit();           // 右上
    static unsigned int GetStraightDownBit();      // 下直進
    static unsigned int GetStraightLeftBit();      // 左直進
    static unsigned int GetStraightRightBit();     // 右直進
    static unsigned int GetStraightUpBit();        // 上直進
    static unsigned int GetStraightLeftDownBit();  // 左下直進
    static unsigned int GetStraightRightDownBit(); // 右下直進
    static unsigned int GetStraightLeftUpBit();    // 左上直進
    static unsigned int GetStraightRightUpBit();   // 右上直進
    static unsigned int GetLeftDoubleUpBit();      // 左上上
    static unsigned int GetRightDoubleUpBit();     // 右上上


    static unsigned int GetGoldMovementBits(); // 金の動きのビット列
};
