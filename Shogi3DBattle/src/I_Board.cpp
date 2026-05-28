#include"I_Board.h"
#include"CubeVertices.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"

float I_Board::GetBoardSize(){return _sideLength;} // 将棋盤1辺の長さを返す

// 指定されたサイズの将棋盤頂点集合作成
I_Board::I_Board(GameObjType gameObjType, float sideLength)
    :I_GameObj(gameObjType), _sideLength(sideLength)
{
    SetVertices(std::make_unique<CubeVertices>(sideLength));

    auto verticesPtr = GetVertices();
    verticesPtr->SetGameObjId(GameObjIdManager::GetId());
    verticesPtr->SetBasicTexId    (static_cast<unsigned char>(BasicTexType::YELLOW_WOOD));
    verticesPtr->SetMulDesignTexId(static_cast<unsigned char>(gameObjType));

    auto worldMatPtr = GetWorldMat();
    auto worldMat = worldMatPtr->GetMat();
    auto halfSideLength = sideLength / 2.0f;
    auto newWorldMat = worldMat * DirectX::XMMatrixTranslation(halfSideLength, halfSideLength, halfSideLength);
    worldMatPtr->SetMat(newWorldMat);
}