#include"PieceFactory.h"
#include<array>
#include<algorithm>

// 駒作成
void PieceFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UINT id)
{
    shogiObj->SetId(id);

    

    
    //float height = (320.0f / 350.0f) * 10.0f;

   

    float mmWidth;
    float mmHeight;
    switch (shogiObjType)
    {
    case ShogiObj::KING:
        mmWidth  = 285.0f;
        mmHeight = 320.0f;
        break;
    
    case ShogiObj::ROOK:
    case ShogiObj::BISHOP:
        mmWidth  = 260.0f;
        mmHeight = 300.0f;
        break;

    case ShogiObj::GOLD:
    case ShogiObj::SILVER:
        mmWidth  = 250.0f;
        mmHeight = 285.0f;
        break;
    
    case ShogiObj::KNIGHT:
        mmWidth  = 235.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::LANCE:
        mmWidth  = 225.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::PAWN:
        mmWidth  = 225.0f;
        mmHeight = 260.0f;
        break;

    default:
        return;
    }

    // 10.0fで約400mm
    float mmPerFloat = 400.0f / 10.0f;

    // floatの半径の長さに直す
    float width  = mmWidth  / mmPerFloat; // 底面横の長さ
    float height = mmHeight / mmPerFloat; // 縦の長さ
    float cornerWidth  = width  * 0.7;    // 角部分の横の長さ
    float cornerHeight = height * 0.85;   // 角部分縦の底面からの高さ
    float thickness    = height / 8.0f;  // 駒の厚み

    // (0,0)を基準とした頂点座標にするため、縦横をずらす
    width        /= 2;
    height       /= 2;
    cornerWidth  /= 2;
    cornerHeight -= height;

    std::vector<ShogiObj::Vert> vertices;

    vertices = // 頂点集合
    {   // 上面図と考えて指定
        // 前面
        {{     -width,     -height, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, id}, // 左下
        {{      width,     -height, -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, id}, // 右下
        {{-cornerWidth, cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, id}, // 左上
        {{ cornerWidth, cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, id}, // 右上
        {{        0.0f,      height, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, id}, // 上    

        // 裏面
        {{      -width,     -height,      0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, id}, // 左下
        {{       width,     -height,      0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, id}, // 右下
        {{-cornerWidth,  cornerHeight,      0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, id}, // 左上
        {{ cornerWidth,  cornerHeight,      0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, id}, // 右上
        {{        0.0f,       height,      0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, id}, // 上
    };

    shogiObj->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum PieceVertName // 駒の頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上
        frontTop,         // 上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
        backTop          // 上
    };

    indices = // インデックス集合
    {
        // 前面
        frontRightBottom, frontLeftBottom, frontLeftTop,     // 右下　左下　左上
        frontLeftTop,     frontRightTop,   frontRightBottom, // 左上　右上 右下
        frontTop,         frontRightTop,   frontLeftTop,     // 右上　左上　上

        // 裏面
        backLeftBottom,  backRightBottom, backLeftTop, // 左下　右下　左上
        backRightBottom, backRightTop,    backLeftTop, // 右下　右上　左上
        backLeftTop,     backRightTop,    backTop,     // 左上　右上　上

        // 側面上左
        frontTop, frontLeftTop, backLeftTop, // 前面上　前面左上　背面左上
        backTop,  frontTop,     backLeftTop, // 背面上　前面上　　背面左上

        // 側面上右
        backTop,  backRightTop, frontRightTop, // 背面上　背面右上　前面右上
        frontTop, backTop,      frontRightTop, // 前面上　背面上　　前面右上　


        // 側面右
        frontRightBottom, frontRightTop, backRightBottom, // 背面右下　前面右上　背面右下
        frontRightTop,    backRightTop,  backRightBottom, // 背面右上　背面右上　背面右下

        // 側面左
        backLeftBottom, backLeftTop,  frontLeftBottom, // 背面左下　背面左上　前面左下
        backLeftTop,    frontLeftTop, frontLeftBottom, // 背面左上　前面左上　前面左下

        // 底面
        frontLeftBottom, frontRightBottom, backRightBottom, // 前面左下　前面右下　背面右下
        frontLeftBottom, backRightBottom, backLeftBottom    // 前面左下　背面右下　背面左下
    };

    shogiObj->SetIndices(indices);
}

PieceFactory::~PieceFactory(){}