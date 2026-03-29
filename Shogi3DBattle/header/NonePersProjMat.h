#pragma once

#include"IMat.h"
#include"ClipZRange.h"

class NonePersProjMat : public IMat, public ClipZRange
{
private:
    float _width;  // 横サイズ
    float _height; // 縦サイズ

public:
    DirectX::XMMATRIX GetMat() override; // パースを使用しないプロジェクション行列を返す

    void  SetWidth (float width);  // 横サイズセット
    float GetWidth();              // 横サイズを返す
    void  SetHeight(float height); // 縦サイズ比セット
    float GetHeight();             // 縦サイズを返す

    NonePersProjMat();
    ~NonePersProjMat();
};