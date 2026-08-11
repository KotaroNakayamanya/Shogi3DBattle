#include"I_Board.h"
#include"CubeVertices.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"

float I_Board::GetSideLength(){return _sideLength;} // 将棋盤1辺の長さを返す

I_Board::I_Board(GameObjType gameObjType, float sideLength)
    :I_GameObj(gameObjType), _sideLength(sideLength)
{
    // 箱型の頂点集合を作成
    SetVertices(std::make_unique<CubeVertices>(gameObjType, BasicTexType::YELLOW_WOOD, sideLength));

    // 頂点集合の乗算エフェクト1番目をセット
    auto vertices = GetVertices();
    vertices->SetMulEffectTexId(1);

    // ワールド行列を将棋盤のマス位置(x,y)の中心点が座標(10x,10y,0)に対応するように調整する
    auto worldMatPtr = GetWorldMat();
    auto worldMat = worldMatPtr->GetMat();
    auto halfSideLength = sideLength / 2.0f;
    auto newWorldMat = worldMat * DirectX::XMMatrixTranslation(halfSideLength, halfSideLength, halfSideLength);
    worldMatPtr->SetMat(newWorldMat);
}