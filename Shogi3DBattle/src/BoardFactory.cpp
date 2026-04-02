#include"BoardFactory.h"

// 将棋盤作成
void BoardFactory::CreateShogiObj(ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType, UCHAR objId)
{
    shogiObj->SetObjId(objId);

    UCHAR texId = static_cast<UINT>(shogiObjType);
    shogiObj->SetTexId(texId);
    
    float size = 100.0f;

    float thickness = size * 0.8f;

    std::vector<ShogiObj::Vert> vertices;

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
    shogiObj->SetVertices(vertData);



    // ワールド行列セット
    DirectX::XMMATRIX worldMat;
    switch (shogiObjType)
    {
        float rate;
    case ShogiObj::BOARD_55:
        rate = 60.0f / 100.0f;
        worldMat = DirectX::XMMatrixScaling(rate, rate, rate);
        break;

    case ShogiObj::BOARD_99:
    default:
        worldMat = DirectX::XMMatrixIdentity();
        break;
    }
    WorldMat worldMatObj;
    worldMatObj.SetWorldMat(worldMat);
    shogiObj->SetWorldMat(worldMatObj);
}