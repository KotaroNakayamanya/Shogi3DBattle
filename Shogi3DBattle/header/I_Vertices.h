#pragma once

class I_Vertices
{
public:
    virtual void SetGameObjId     (unsigned char id) = 0; // ゲームオブジェクトIDセット
    virtual void SetBasicTexId    (unsigned char id) = 0;// 基本テクスチャセット
    virtual void SetMulDesignTexId(unsigned char id) = 0;// 乗算描画テクスチャセット
};