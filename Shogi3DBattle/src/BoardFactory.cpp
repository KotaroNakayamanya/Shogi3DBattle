#include"BoardFactory.h"

// 将棋盤作成
void BoardFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UINT objId)
{
    shogiObj->SetObjId(objId);

    UINT texId = static_cast<UINT>(shogiObjType);
    shogiObj->SetTexId(texId);
    
    float size = 60.0f;

    float thickness = size * 0.8f;

    std::vector<ShogiObj::Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{size, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}, objId}, // 右上
        {{size, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}, objId}, // 右下
        {{0.0f, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}, objId}, // 左下
        {{0.0f, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, objId}, // 左上

        // 側面上
        {{0.0f, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右上
        {{0.0f, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右下
        {{size, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左下
        {{size, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左上

        // 側面右
        {{size, size, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右上
        {{size, size, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右下
        {{size, 0.0f, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左下
        {{size, 0.0f, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左上

        // 側面下
        {{size, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右上
        {{size, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右下
        {{0.0f, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左下
        {{0.0f, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左上

        // 側面左
        {{0.0f, 0.0f, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右上
        {{0.0f, 0.0f, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 右下
        {{0.0f, size, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左下
        {{0.0f, size, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, objId}, // 左上        
    };

    shogiObj->SetVertices(vertices);


    std::vector<unsigned short> indices;

    // (0 1 2) (2 3 0)で作れる
    for (UINT i = 0; i < 5; i++)
    {
        UINT offset = 4 * i;

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);

        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);
    }

    //enum BoardVertName // 将棋盤の頂点に名前を付ける
    //{
    //    // 前面
    //    frontLeftBottom,  // 左下
    //    frontRightBottom, // 右下
    //    frontLeftTop,     // 左上
    //    frontRightTop,    // 右上

    //    // 背面
    //    backLeftBottom,  // 左下
    //    backRightBottom, // 右下
    //    backLeftTop,     // 左上
    //    backRightTop,    // 右上
    //};

    //indices =
    //{
    //    // 前面
    //    frontRightBottom, frontLeftBottom,  frontLeftTop,
    //    frontLeftTop,     frontRightTop,    frontRightBottom,     
    //    
    //    // 上側面
    //    frontRightTop, frontLeftTop, backLeftTop, 
    //    backLeftTop,   backRightTop, frontRightTop,

    //    // 右側面
    //    frontRightBottom, frontRightTop,   backRightTop,
    //    backRightTop,     backRightBottom, frontRightBottom,

    //    // 下側面
    //    frontLeftBottom, frontRightBottom, backRightBottom,
    //    backRightBottom, backLeftBottom,   frontLeftBottom,

    //    // 左側面
    //    frontLeftTop, frontLeftBottom, backLeftBottom,
    //    backLeftBottom, backLeftTop, frontLeftTop,

    //    // 背面
    //    backRightBottom, backLeftBottom, backLeftTop,
    //    backLeftTop,     backRightTop,   backRightBottom
    //};
    shogiObj->SetIndices(indices);
}

BoardFactory::BoardFactory(){}
BoardFactory::~BoardFactory(){}