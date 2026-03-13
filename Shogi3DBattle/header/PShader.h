#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class PShader
{
    friend class Device; // DirectX3Dデバイス参照可能
    
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _pShaderBlob; // ピクセルシェーダバイナリオブジェクト

public:
    ID3DBlob* GetPShaderBlob();  // ピクセルシェーダーバイナリを渡す

    PShader();
    ~PShader();
};