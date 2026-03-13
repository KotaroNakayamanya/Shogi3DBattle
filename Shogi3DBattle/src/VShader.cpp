#include"VShader.h"

ID3DBlob* VShader::GetVShaderBlob(){return _vShaderBlob.Get();} // 頂点シェーダーバイナリを返す

VShader::VShader(){}
VShader::~VShader(){}