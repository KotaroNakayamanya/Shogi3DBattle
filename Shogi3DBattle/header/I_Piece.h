#pragma once

#include"I_GameObj.h"
#include"PlayerSide.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
private:
    PlayerSide _playerSide; // 駒所有者プレイヤー
public:
    //void SetPlayerSide(PlayerSide playerSide); // 駒所有者プレイヤーセット
    void Move(DirectX::XMFLOAT3 vec); // 移動

    I_Piece(float mmBottomWidth, float mmHeight, GameObjType pieceType, PlayerSide playerSide);
    virtual ~I_Piece() = default;
};