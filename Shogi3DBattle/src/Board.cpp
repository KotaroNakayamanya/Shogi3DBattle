#include"Board.h"

Board::Board(BoardSize size)
{
    if (size == five) // 5*5にする
    {
        Board();
        return;
    }

}
Board::Board()
{
    _vertices =
    {   // 上面図

        // 前面
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左下
        {{0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 右上

        // 背面
        {{0.0f, 0.0f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左下
        {{0.5f, 0.0f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f, 0.5f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // 左上
        {{0.5f, 0.5f, 0.3f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}  // 右上
    };

    _indices =
    {
        // 前面
        frontRightBottom, frontLeftBottom,  frontLeftTop,
        frontLeftTop,     frontRightTop,    frontRightBottom,     
        
        // 上側面
        frontRightTop, frontLeftTop, backLeftTop, 
        backLeftTop,   backRightTop, frontRightTop,

        // 右側面
        frontRightBottom, frontRightTop,   backRightTop,
        backRightTop,     backRightBottom, frontRightBottom,

        // 下側面
        frontLeftBottom, frontRightBottom, backRightBottom,
        backRightBottom, backLeftBottom,   frontLeftBottom,

        // 左側面
        frontLeftTop, frontLeftBottom, backLeftBottom,
        backLeftBottom, backLeftTop, frontLeftTop,

        // 背面
        backRightBottom, backLeftBottom, backLeftTop,
        backLeftTop,     backRightTop,   backRightBottom
    };
}
Board::~Board(){}