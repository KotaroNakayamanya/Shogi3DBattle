#include"BoardVerticesFactory.h"
#include"Vertices.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"
#include"GameObjType.h"


// 頂点集合作成
std::unique_ptr<I_BufferedData> BoardVerticesFactory::CreateUniquePtr()
{
    float size = 100.0f;

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

    std::unique_ptr<Vertices> uniquePtr = std::make_unique<Vertices>();
    uniquePtr->SetDatas(vertices);
    uniquePtr->SetGameObjId(GameObjIdManager::GetId());
    uniquePtr->SetBasicTexId    (static_cast<unsigned char>(BasicTexType::YELLOW_WOOD));
    uniquePtr->SetMulDesignTexId(static_cast<unsigned char>(GameObjType ::BOARD_99));

    return uniquePtr;
}