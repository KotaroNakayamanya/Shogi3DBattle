#pragma once

#include"I_GameObj.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
protected:
    void SetPieceVertices(float mmBottomWidth, float mmHeight); // ‹î‚Ì’¸“_W‡ì¬

public:
    void Move(DirectX::XMFLOAT3 vec); // ˆÚ“®

    virtual ~I_Piece() = default;
};