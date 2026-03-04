#pragma once

#include<d3dcompiler.h>
#include<wrl.h>

class Shader
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3DBlob> _vertexShaderBlob; // 頂点シェーダーバイナリオブジェクト
    ComPtr<ID3DBlob> _pixelShaderBlob; // ピクセルシェーダバイナリオブジェクト


    HRESULT CreateVertexShaderBlob(); // 頂点シェーダロード
    HRESULT CreatePixelShaderBlob();  // ピクセルシェーダロード

public:
    // シェーダーバイナリ作成
    HRESULT CreateShaderBlob(); 
    // 頂点シェーダーバイナリを渡す
    ID3DBlob* GetVertexShaderBlob();
    // ピクセルシェーダーバイナリを渡す
    ID3DBlob* GetPixelShaderBlob();

    Shader();
    ~Shader();
};