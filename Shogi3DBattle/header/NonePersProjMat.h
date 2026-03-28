#pragma once

#include"IProjMat.h"

class NonePersProjMat : public IProjMat
{
private:
    float _width;  // 横サイズ
    float _height; // 縦サイズ

public:
    // パースを使用しないプロジェクション行列を返す
    DirectX::XMMATRIX GetMat() override;

    void SetWidth (float width);  // 横サイズセット
    void SetHeight(float height); // 縦サイズ比セット

    NonePersProjMat();
    ~NonePersProjMat();
};