#include"PieceFactory.h"
#include<array>
#include<algorithm>

// 駒作成
void PieceFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UINT id)
{
    shogiObj->SetId(id);

    UINT texId = static_cast<UINT>(shogiObjType);
    shogiObj->SetTexId(texId);   

    float mmBottomWidth;
    float mmHeight;
    switch (shogiObjType)
    {
    case ShogiObj::KING:
        mmBottomWidth  = 285.0f;
        mmHeight = 320.0f;
        break;
    
    case ShogiObj::ROOK:
    case ShogiObj::BISHOP:
        mmBottomWidth  = 260.0f;
        mmHeight = 300.0f;
        break;

    case ShogiObj::GOLD:
    case ShogiObj::SILVER:
        mmBottomWidth  = 250.0f;
        mmHeight = 285.0f;
        break;
    
    case ShogiObj::KNIGHT:
        mmBottomWidth  = 235.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::LANCE:
        mmBottomWidth  = 225.0f;
        mmHeight = 275.0f;
        break;

    case ShogiObj::PAWN:
        mmBottomWidth  = 225.0f;
        mmHeight = 260.0f;
        break;

    default:
        return;
    }

    // 10.0fで約400mm
    float mmPerFloat = 400.0f / 10.0f;

    // マスの1辺を1.0fとして、駒をfloatの長さに直す
    float bottomWidth  = mmBottomWidth  / mmPerFloat; // 底面横の長さ
    float height = mmHeight / mmPerFloat; // 縦の長さ

    float cornerWidthRate  = 0.7;  // 底面横に対する角横長さの比率
    float cornerHeightRate = 0.85; // 駒の高さに対する角縦長さの比率

    float cornerWidth  = bottomWidth  * cornerWidthRate;    // 角部分の横の長さ
    float cornerHeight = height * cornerHeightRate;   // 角部分縦の底面からの高さ
    float thickness    = height / 8.0f;  // 駒の厚み

    // UV座標使用のため、駒の高さを1.0fとした時のそれぞれの頂点のUV座標を計算する
    float quarterCornerWidth = (cornerWidth / height) / 2 / 2;
    float quarterBottomWidth = (bottomWidth / height) / 2 / 2;

    float frontCenterU = 0.25f;

    // 表面
    float frontTopU = frontCenterU;
    float topV = 0.0f;

   
    float frontLeftCornerU  = frontCenterU - quarterCornerWidth;
    float frontRightCornerU = frontCenterU + quarterCornerWidth;
    float cornerV = (1.0f - cornerHeightRate) / 2;

    
    float frontLeftBottomU  = frontCenterU - quarterBottomWidth;
    float frontRightBottomU = frontCenterU + quarterBottomWidth;
    float bottomV = 0.5f;

    // 裏面
    float backTopU = frontTopU + 0.5f;
    float backLeftCornerU  = frontLeftCornerU + 0.5f;
    float backRightCornerU = frontRightCornerU + 0.5f;
    float backLeftBottomU  = frontLeftBottomU + 0.5f;
    float backRightBottomU = frontRightBottomU + 0.5f;
    

    // (0,0)を基準とした頂点座標にするため、縦横をずらす
    bottomWidth  /= 2;
    height       /= 2;
    cornerWidth  /= 2;
    cornerHeight -= height;

    

    

    std::vector<ShogiObj::Vert> vertices;

    vertices = // 頂点集合
    {   // 上面図と考えて指定
        // 前面
        {{-bottomWidth,     -height, -thickness}, {0.0f, 0.0f, -1.0f}, {frontLeftBottomU, bottomV}, id, texId}, // 左下
        {{ bottomWidth,     -height, -thickness}, {0.0f, 0.0f, -1.0f}, {frontRightBottomU, bottomV}, id, texId}, // 右下
        {{-cornerWidth, cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {frontLeftCornerU, cornerV}, id, texId}, // 左上
        {{ cornerWidth, cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {frontRightCornerU, cornerV}, id, texId}, // 右上
        {{        0.0f,      height, -thickness}, {0.0f, 0.0f, -1.0f}, {frontTopU, topV}, id, texId}, // 上    

        // 裏面
        {{-bottomWidth,     -height,      0.0f}, {0.0f, 0.0f, 1.0f}, {backRightBottomU, bottomV}, id, texId}, // 左下
        {{ bottomWidth,     -height,      0.0f}, {0.0f, 0.0f, 1.0f}, {backLeftBottomU, bottomV}, id, texId}, // 右下
        {{-cornerWidth,  cornerHeight,      0.0f}, {0.0f, 0.0f, 1.0f}, {backRightCornerU, cornerV}, id, texId}, // 左上
        {{ cornerWidth,  cornerHeight,      0.0f}, {0.0f, 0.0f, 1.0f}, {backLeftCornerU, cornerV}, id, texId}, // 右上
        {{        0.0f,       height,      0.0f}, {0.0f, 0.0f, 1.0f}, {backTopU, topV}, id}, // 上
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