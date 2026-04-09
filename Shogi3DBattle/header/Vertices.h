#pragma once

#include"I_Vertices.h"
#include"B_NaturalBufferedData.h"
#include"VertStruct.h"

class Vertices : public I_Vertices, public B_NaturalBufferedData<Vert>
{
public:
    void SetGameObjId     (unsigned char id) override; // ゲームオブジェクトIDセット
    void SetBasicTexId    (unsigned char id) override; // 基本テクスチャセット
    void SetMulDesignTexId(unsigned char id) override; // 乗算描画テクスチャセット
};