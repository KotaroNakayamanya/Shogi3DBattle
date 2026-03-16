#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class PShader
{
    friend class Device; // DirectX3Dデバイス参照可能
    
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _pShader; // ピクセルシェーダー

public:
    ID3DBlob* GetPShader();  // ピクセルシェーダーを返す

    PShader();
    ~PShader();
};