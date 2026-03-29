#include"NonePersProjMat.h"

// パースを使用しないプロジェクション行列を返す
DirectX::XMMATRIX NonePersProjMat::GetMat()
{
    return DirectX::XMMatrixOrthographicLH(_width, _height, _nearZ, _farZ);
}

void  NonePersProjMat::SetWidth (float width) {_width  = width;}  // 横サイズセット
float NonePersProjMat::GetWidth()             {return _width;}    // 横サイズを返す
void  NonePersProjMat::SetHeight(float height){_height = height;} // 縦サイズ比セット
float NonePersProjMat::GetHeight()            {return _height;}   // 縦サイズを返す

NonePersProjMat::NonePersProjMat(){}
NonePersProjMat::~NonePersProjMat(){}