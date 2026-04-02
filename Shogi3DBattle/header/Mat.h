#pragma once

#include<DirectXMath.h>
#include"BufferedData.h"

class Mat : public BufferedData<DirectX::XMMATRIX>
{
public:
    virtual DirectX::XMMATRIX GetMat() = 0; // 行列を返す
    std::vector<DirectX::XMMATRIX> GetDatas() override {return {GetMat()};} // データ集合を返す（要素数１）

    virtual ~Mat() = default;
};