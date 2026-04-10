#pragma once

#include"I_GameObj.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
protected:
    std::unique_ptr<Vertices> CreatePieceVertices(float mmBottomWidth, float mmHeight); // 指定されたサイズの駒の頂点集合作成

public:
    void Move(DirectX::XMFLOAT3 vec); // 移動

    virtual ~I_Piece() = default;
};