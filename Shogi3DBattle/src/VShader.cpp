#include"VShader.h"

ID3DBlob* VShader::GetVShader(){return _vShader.Get();} // 頂点シェーダーバイナリを返す

VShader::VShader(){}
VShader::~VShader(){}