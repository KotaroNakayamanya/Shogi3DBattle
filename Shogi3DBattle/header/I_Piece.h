#pragma once

#include"I_GameObj.h"
#include"PlayerSide.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
private:
    PlayerSide _playerSide; // 駒所有プレイヤー

public:
    void Move(DirectX::XMFLOAT3 vec); // 移動

    void       SetPlayerSide(PlayerSide playerSide); // 駒所有プレイヤーセット
    PlayerSide GetPlayerSide();                      // 駒所有プレイヤーを返す

    I_Piece(float mmBottomWidth, float mmHeight, GameObjType pieceType, PlayerSide playerSide);
    virtual ~I_Piece() = default;
};