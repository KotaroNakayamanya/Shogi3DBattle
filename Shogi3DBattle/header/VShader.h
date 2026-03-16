#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class VShader
{
    friend class Device; // DirectX3Dデバイス参照可能
    
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _vShader; // 頂点シェーダー

public:
    ID3DBlob* GetVShader();  // 頂点シェーダーを返す

    VShader();
    ~VShader();
};