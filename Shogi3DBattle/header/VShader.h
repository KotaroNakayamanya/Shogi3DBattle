#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class VShader
{
    friend class Device; // DirectX3Dデバイス参照可能
    
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _vShaderBlob; // 頂点シェーダバイナリオブジェクト

public:
    ID3DBlob* GetVShaderBlob();  // 頂点シェーダーバイナリを渡す

    VShader();
    ~VShader();
};