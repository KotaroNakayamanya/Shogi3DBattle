#pragma once

#include"ShogiObj.h"
#include"VertexStruct.h"

class Board : public ShogiObj
{
private:
    enum BoardSize
    {
        five, // 5*5
        nine  // 9*9
    };

    enum VertexName // 頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
    };

public:
    void ResizeBoard(BoardSize size); // ボードサイズ変更

    Board(BoardSize size);
    Board();
    ~Board();
};