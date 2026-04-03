#include"BoardFactory.h"

// 将棋盤作成
void BoardFactory::CreateGameObj(GameObj* gameObj, GameObj::GameObjType gameObjType, unsigned char objId)
{
    gameObj->SetObjId(objId);

    unsigned char texId = static_cast<unsigned char>(gameObjType);
    gameObj->SetTexId(texId);
    
    float size = 100.0f;

    float thickness = size * 0.8f;

    std::vector<GameObj::Vert> vertices;

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

    for (auto& vertex : vertices)
    {
        vertex.objId = objId;
        vertex.designTexId = texId;
    }

    NaturalBufferedData<GameObj::Vert> vertData;
    vertData.SetDatas(vertices);
    gameObj->SetVertices(vertData);



    // ワールド行列セット
    DirectX::XMMATRIX worldMat;
    switch (gameObjType)
    {
        float rate;
    case GameObj::BOARD_55:
        rate = 60.0f / 100.0f;
        worldMat = DirectX::XMMatrixScaling(rate, rate, rate);
        break;

    case GameObj::BOARD_99:
    default:
        worldMat = DirectX::XMMatrixIdentity();
        break;
    }
    WorldMat worldMatObj;
    worldMatObj.SetWorldMat(worldMat);
    gameObj->SetWorldMat(worldMatObj);
}