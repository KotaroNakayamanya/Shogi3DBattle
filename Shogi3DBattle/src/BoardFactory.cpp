#include"BoardFactory.h"
#include"BoardVerticesFactory.h"
#include"WorldMatFactory.h"
#include"FactoryMethod.h"
#include"Board.h"
#include"VertStruct.h"

//// 将棋盤作成
//void BoardFactory::CreateGameObj(GameObj* gameObj, GameObj::GameObjType gameObjType, unsigned char objId)
//{
//    gameObj->SetObjId(objId);
//
//    unsigned char texId = static_cast<unsigned char>(gameObjType);
//    gameObj->SetTexId(texId);
//    
//    float size = 100.0f;
//
//    float thickness = size * 0.8f;
//
//    std::vector<Vert> vertices;
//
//    vertices =
//    {   // 上面図
//
//        // 前面
//        {{size, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}}, // 右上
//        {{size, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}}, // 右下
//        {{0.0f, 0.0f, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}}, // 左下
//        {{0.0f, size, 0.0f     },  { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}}, // 左上
//
//        // 側面上
//        {{0.0f, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
//        {{0.0f, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
//        {{size, size, thickness},  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
//        {{size, size, 0.0f     },  { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上
//
//        // 側面右
//        {{size, size, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
//        {{size, size, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
//        {{size, 0.0f, thickness},  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
//        {{size, 0.0f, 0.0f     },  { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上
//
//        // 側面下
//        {{size, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
//        {{size, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
//        {{0.0f, 0.0f, thickness},  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
//        {{0.0f, 0.0f, 0.0f     },  { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}}, // 左上
//
//        // 側面左
//        {{0.0f, 0.0f, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右上
//        {{0.0f, 0.0f, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 右下
//        {{0.0f, size, thickness},  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左下
//        {{0.0f, size, 0.0f     },  {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // 左上        
//    };
//
//    for (auto& vertex : vertices)
//    {
//        vertex.objId = objId;
//        vertex.designTexId = texId;
//    }
//
//    NaturalBufferedData<Vert> vertData;
//    vertData.SetDatas(vertices);
//    gameObj->SetVertices(vertData);
//
//
//
//    // ワールド行列セット
//    DirectX::XMMATRIX worldMat;
//    switch (gameObjType)
//    {
//        float rate;
//    case GameObj::BOARD_55:
//        rate = 60.0f / 100.0f;
//        worldMat = DirectX::XMMatrixScaling(rate, rate, rate);
//        break;
//
//    case GameObj::BOARD_99:
//    default:
//        worldMat = DirectX::XMMatrixIdentity();
//        break;
//    }
//    WorldMat worldMatObj;
//    worldMatObj.SetWorldMat(worldMat);
//    gameObj->SetWorldMat(worldMatObj);
//}

// 将棋盤作成
std::unique_ptr<GameObj> BoardFactory::CreateUniquePtr()
{   
    std::unique_ptr<Board> uniquePtr = std::make_unique<Board>();

    // ゲームオブジェクトタイプ　9×9将棋盤をセット
    uniquePtr->SetGameObjType(GameObjType::BOARD_99);

    // 頂点集合作成
    _verticesFactory.reset(new BoardVerticesFactory());
    auto vertices =
        FactoryMethod::GetDownCastUniquePtr<Vertices, IBufferedDataFactory<Vert>>(_verticesFactory.get());
    auto verticesPtr = vertices.get();
    vertices.release();
    uniquePtr->SetVertices(verticesPtr);

    // ワールド行列作成
    _matFactory.reset(new WorldMatFactory());
    auto mat = 
        FactoryMethod::GetDownCastUniquePtr<WorldMat, IBufferedDataFactory<DirectX::XMMATRIX>>(_matFactory.get());
    auto matPtr = mat.get();
    mat.release();
    uniquePtr->SetWorldMat(matPtr);
    
    return uniquePtr;
}