#include"PShader.h"

ID3DBlob* PShader::GetPShaderBlob(){return _pShaderBlob.Get();} // ピクセルシェーダーバイナリを返す

PShader::PShader(){}
PShader::~PShader(){}