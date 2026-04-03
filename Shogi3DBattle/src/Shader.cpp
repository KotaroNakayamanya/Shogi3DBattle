#include"Shader.h"

void      Shader::SetShader(ComPtr<ID3DBlob> shader){_shader = shader;}     // シェーダーセット
ID3DBlob* Shader::GetShader()                       {return _shader.Get();} // シェーダーを返す
