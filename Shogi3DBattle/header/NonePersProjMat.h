#pragma once

#include"I_ProjMat.h"

class NonePersProjMat : public I_ProjMat
{
private:
    float _width;  // 横サイズ
    float _height; // 縦サイズ

public:
    DirectX::XMMATRIX GetMat() override; // パースを使用しないプロジェクション行列を返す

    void  SetWidth (float width);  // 横サイズセット
    float GetWidth();              // 横サイズを返す
    void  SetHeight(float height); // 縦サイズ比セット

    NonePersProjMat(
        float width  = 100.0f,
        float height = 100.0f,
        float nearZ  =   1.0f,
        float farZ   =  50.0f);
};