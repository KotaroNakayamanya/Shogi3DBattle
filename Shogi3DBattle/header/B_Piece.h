#pragma once

#include"I_Piece.h"
#include"B_GameObj.h"

class B_Piece : public I_Piece, public B_GameObj
{
public:
    // 移動
    void Move(DirectX::XMFLOAT3 vec) override
    {
        auto worldMat = _worldMat->GetMat();
        worldMat *= DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
        _worldMat->SetWorldMat(worldMat);
    }

    Vertices* GetVertices() override {return _vertices.get();} // 頂点集合を返す

    void      SetWorldMat(WorldMat* mat) override {_worldMat.reset(mat);} // ワールド行列セット
    WorldMat* GetWorldMat()              override {return _worldMat.get();}// ワールド行列を返す
};