#pragma once

#include"B_GameObj.h"

class B_Piece : public B_GameObj
{
public:
    // ˆÚ“®
    void Move(DirectX::XMFLOAT3 vec)
    {
        auto worldMat = _worldMat->GetMat();
        worldMat *= DirectX::XMMatrixTranslation(vec.x, vec.y, vec.z);
        _worldMat->SetMat(worldMat);
    }
};