#include"I_Board.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"

// 指定されたサイズの将棋盤頂点集合作成
I_Board::I_Board(float size)
{
    float thickness = size * 0.8f;

    std::vector<Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{size, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // 右上
        {{size, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // 右下
        {{0.0f, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // 左下
        {{0.0f, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上

        // 側面上
        {{0.0f, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{0.0f, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{size, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{size, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面右
        {{size, size, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{size, size, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{size, 0.0f, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{size, 0.0f, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面下
        {{size, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{size, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面左
        {{0.0f, 0.0f, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{0.0f, 0.0f, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f, size, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f, size, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上        
    };

    SetVertices(std::make_unique<Vertices>());
    auto verticesPtr = GetVertices();
    verticesPtr->SetDatas(vertices);
    verticesPtr->SetGameObjId(GameObjIdManager::GetId());
    verticesPtr->SetBasicTexId    (static_cast<unsigned char>(BasicTexType::YELLOW_WOOD));
}