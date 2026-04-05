#pragma once

#include"NaturalBufferedData.h"
#include"VertStruct.h"

class Vertices : public NaturalBufferedData<Vert>
{
public:
    void SetGameObjId     (unsigned char id); // ゲームオブジェクトIDセット
    void SetBasicTexId    (unsigned char id); // 基本テクスチャセット
    void SetMulDesignTexId(unsigned char id); // 乗算描画テクスチャセット
};