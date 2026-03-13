#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class Shader
{
    friend class Device; // DirectX3Dデバイス参照可能
    
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _vShaderBlob; // 頂点シェーダーバイナリオブジェクト
    ComPtr<ID3DBlob> _pShaderBlob; // ピクセルシェーダバイナリオブジェクト

public:
    ID3DBlob* GetVertexShaderBlob(); // 頂点シェーダーバイナリを渡す
    ID3DBlob* GetPixelShaderBlob();  // ピクセルシェーダーバイナリを渡す

    Shader();
    ~Shader();
};