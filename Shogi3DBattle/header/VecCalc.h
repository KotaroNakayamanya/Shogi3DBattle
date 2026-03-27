#pragma once

#include<DirectXMath.h>

class VecCalc
{
public:
    static::DirectX::XMFLOAT3 GetNormFloat( // ê≥ãKâª
        DirectX::XMFLOAT3 f);
    static::DirectX::XMFLOAT2 GetNormFloat( // ê≥ãKâª
        DirectX::XMFLOAT2 f);

    static DirectX::XMFLOAT3 GetFloat3AddFloat3( // XMFLOAT3 + XMFLOAT3
        DirectX::XMFLOAT3 f1,
        DirectX::XMFLOAT3 f2);

    static DirectX::XMFLOAT3 GetFloat3SubFloat3( // XMFLOAT3 - XMFLOAT3
        DirectX::XMFLOAT3 f1,
        DirectX::XMFLOAT3 f2);

    static DirectX::XMFLOAT3 GetFloat3MulMat( // XMFLOAT3 * XMMATRIX
        DirectX::XMFLOAT3 f,
        DirectX::XMMATRIX mat);

    static DirectX::XMFLOAT3 GetFloat3FromVec( // XMVECTOR Å® XMFLOAT3
        DirectX::XMVECTOR v);
    static DirectX::XMFLOAT2 GetFloat2FromVec( // XMVECTOR Å® XMFLOAT2
        DirectX::XMVECTOR v);

    static DirectX::XMFLOAT4X4 GetFoloat4x4FromMat( // XMMATRIX Å® XMFloat4X4
        DirectX::XMMATRIX mat);

    ~VecCalc(){}
};