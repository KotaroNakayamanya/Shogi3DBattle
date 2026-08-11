#include"CubeVertices.h"
#include"GameObjIdManager.h"

CubeVertices::CubeVertices(GameObjType gameObjType, BasicTexType basicTexType, float sideLength)
{
    auto halfSideLength = sideLength / 2.0f;

    std::vector<Vert> vertices(24);
    vertices =
    {   // 上面図

        // 上面
        {{ halfSideLength,  halfSideLength, -halfSideLength},  { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // 右上
        {{ halfSideLength, -halfSideLength, -halfSideLength},  { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // 右下
        {{-halfSideLength, -halfSideLength, -halfSideLength},  { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // 左下
        {{-halfSideLength,  halfSideLength, -halfSideLength},  { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上

        // 底面
        {{-halfSideLength,  halfSideLength,  halfSideLength},  { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // 右上
        {{-halfSideLength, -halfSideLength,  halfSideLength},  { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // 右下
        {{ halfSideLength, -halfSideLength,  halfSideLength},  { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // 左下
        {{ halfSideLength,  halfSideLength,  halfSideLength},  { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}, // 左上

        // 側面上
        {{-halfSideLength,  halfSideLength, -halfSideLength},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{-halfSideLength,  halfSideLength,  halfSideLength},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{ halfSideLength,  halfSideLength,  halfSideLength},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{ halfSideLength,  halfSideLength, -halfSideLength},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面右
        {{ halfSideLength,  halfSideLength, -halfSideLength},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{ halfSideLength,  halfSideLength,  halfSideLength},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{ halfSideLength, -halfSideLength,  halfSideLength},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{ halfSideLength, -halfSideLength, -halfSideLength},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面下
        {{ halfSideLength, -halfSideLength, -halfSideLength},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{ halfSideLength, -halfSideLength,  halfSideLength},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{-halfSideLength, -halfSideLength,  halfSideLength},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{-halfSideLength, -halfSideLength, -halfSideLength},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上

        // 側面左
        {{-halfSideLength, -halfSideLength, -halfSideLength},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
        {{-halfSideLength, -halfSideLength,  halfSideLength},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
        {{-halfSideLength,  halfSideLength,  halfSideLength},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
        {{-halfSideLength,  halfSideLength, -halfSideLength},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上        
    };

    auto gameObjId = GameObjIdManager::GetId(); // オブジェクト識別ID取得

    for (auto& vert : vertices)
    {
        vert.gameObjId      = gameObjId;
        vert.basicTexId     = static_cast<unsigned char>(basicTexType);
        vert.mulDesignTexId = static_cast<unsigned char>(gameObjType);
        vert.mulEffectTexId = 0;
    }

    SetDatas(vertices);
}