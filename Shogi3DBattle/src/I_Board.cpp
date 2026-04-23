#include"I_Board.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"

float I_Board::GetBoardSize(){return _boardSize;} // 将棋盤1辺の長さを返す

// 指定されたサイズの将棋盤頂点集合作成
I_Board::I_Board(float boardSize) : _boardSize(boardSize)
{
    float thickness = boardSize * 0.8f;

    std::vector<Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{boardSize, boardSize, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // 右上
        {{boardSize, 0.0f,      0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // 右下
        {{0.0f,      0.0f,      0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // 左下
        {{0.0f,      boardSize, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上

        // 側面上
        {{0.0f,      boardSize, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{0.0f,      boardSize, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{boardSize, boardSize, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{boardSize, boardSize, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面右
        {{boardSize, boardSize, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{boardSize, boardSize, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{boardSize, 0.0f,      thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{boardSize, 0.0f,      0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面下
        {{boardSize, 0.0f,      0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{boardSize, 0.0f,      thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f,      0.0f,      thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f,      0.0f,      0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面左
        {{0.0f,      0.0f,      0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{0.0f,      0.0f,      thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{0.0f,      boardSize, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{0.0f,      boardSize, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上        
    };

    SetVertices(std::make_unique<Vertices>());
    auto verticesPtr = GetVertices();
    verticesPtr->SetDatas(vertices);
    verticesPtr->SetGameObjId(GameObjIdManager::GetId());
    verticesPtr->SetBasicTexId    (static_cast<unsigned char>(BasicTexType::YELLOW_WOOD));
}