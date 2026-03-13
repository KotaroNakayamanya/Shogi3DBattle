#include"Shader.h"

ID3DBlob* Shader::GetVertexShaderBlob(){return _vShaderBlob.Get();} // 頂点シェーダーバイナリを返す
ID3DBlob* Shader::GetPixelShaderBlob(){return _pShaderBlob.Get();} // ピクセルシェーダーバイナリを返す

Shader::Shader(){}
Shader::~Shader(){}