#pragma once

#include"I_GameObj.h"
#include"PlayerSide.h"
#include<DirectXMath.h>

class I_Piece : public I_GameObj
{
private:
    PlayerSide _playerSide;    // 駒所有プレイヤー
    bool       _isPromotion;   // 成っているかどうか
    float      _halfThickness; // 駒の厚みの半分（裏返すときに使用)

public:
    void Move(DirectX::XMFLOAT3 vec); // 移動

    void       SetPlayerSide(PlayerSide playerSide); // 駒所有プレイヤーセット
    PlayerSide GetPlayerSide();                      // 駒所有プレイヤーを返す

    void SetIsPromotion(bool b); // 成っているかどうかセット
    bool GetIsPromotion();       // 成っているかどうか返す

    float GetHalfThickness(); // 駒の厚みの半分のサイズを返す

    virtual unsigned int GetMovementBits() = 0; // 移動出来る範囲をビット列で返す

    I_Piece(float mmBottomWidth, float mmHeight, GameObjType pieceType, PlayerSide playerSide);
    virtual ~I_Piece() = default;
};