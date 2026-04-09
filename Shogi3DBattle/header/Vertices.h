#pragma once

#include"I_NaturalBufferedData.h"
#include"VertStruct.h"

class Vertices : public I_NaturalBufferedData<Vert>
{
public:
    void SetGameObjId     (unsigned char id); // ゲームオブジェクトIDセット
    void SetBasicTexId    (unsigned char id); // 基本テクスチャセット
    void SetMulDesignTexId(unsigned char id); // 乗算描画テクスチャセット
};