#include"BoardFactory.h"

// 将棋盤作成
void BoardFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UINT id)
{
    shogiObj->SetId(id);
    
    float size = 60.0f;

    std::vector<ShogiObj::Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{0.0f, 0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, id}, // 左下
        {{size, 0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, id}, // 右下
        {{0.0f, size, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, id}, // 左上
        {{size, size, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, id}, // 右上

        // 背面
        {{0.0f, 0.0f, 20.0f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, id}, // 左下
        {{size, 0.0f, 20.0f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, id}, // 右下
        {{0.0f, size, 20.0f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, id}, // 左上
        {{size, size, 20.0f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, id}  // 右上
    };

    shogiObj->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum BoardVertName // 将棋盤の頂点に名前を付ける
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

    indices =
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
    shogiObj->SetIndices(indices);
}

BoardFactory::BoardFactory(){}
BoardFactory::~BoardFactory(){}