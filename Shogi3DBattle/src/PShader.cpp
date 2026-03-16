#include"PShader.h"

ID3DBlob* PShader::GetPShader(){return _pShader.Get();} // ピクセルシェーダーを返す

PShader::PShader(){}
PShader::~PShader(){}