#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class Shader
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _shader; // シェーダー

public:
    void      SetShader(ComPtr<ID3DBlob> shader); // シェーダーセット
    ID3DBlob* GetShader();                        // シェーダーを返す
};