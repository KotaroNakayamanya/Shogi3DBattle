#include"SideBoard.h"
#include"CubeVertices.h"

SideBoard::SideBoard() : I_GameObj(GameObjType::SIDEBOARD)
{
    // 箱型の頂点集合を作成
    SetVertices(std::make_unique<CubeVertices>(GameObjType::SIDEBOARD, BasicTexType::BROWN_WOOD, 30.0f));

    // ワールド行列を将棋盤のマス位置(x,y)の中心点が座標(10x,10y,0)に対応するように調整する
    auto worldMatPtr = GetWorldMat();
    auto worldMat = worldMatPtr->GetMat();
    auto newWorldMat = worldMat * DirectX::XMMatrixTranslation(-15.0f, 85.0f, 15.0f);
    worldMatPtr->SetMat(newWorldMat);
}