#pragma once

#include"ShogiObj.h"
#include"VertexStruct.h"

class Piece : public ShogiObj
{
protected:
    DirectX::XMMATRIX _worldMat; // ワールド行列

    typedef struct CreatePieceVerticesArg // 駒の頂点集合作成用引数
    {
        float bottomWidth;  // 底面の横の長さ
        float cornerWidth;  // 角部分の横の長さ
        float height;       // 高さ
        float cornerHeight; // 角部分の高さ
        float thickness;    // 駒の厚み

    }CreatePieceVerticesArg;

    void CreatePieceVertices(CreatePieceVerticesArg arg); // 駒の頂点集合作成

public:
    void MoveX(float x); // x軸方向に動くようにワールド行列を変換する
    void MoveY(float y); // y軸方向に動くようにワールド行列を変換する

    DirectX::XMMATRIX GetWorldMat(); // ワールド行列を返す  

    Piece();
    ~Piece();
};