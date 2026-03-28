#include"NonePersProjMat.h"

// パースを使用しないプロジェクション行列を返す
DirectX::XMMATRIX NonePersProjMat::GetMat()
{
    return DirectX::XMMatrixOrthographicLH(_width, _height, _nearZ, _farZ);
}

void NonePersProjMat::SetWidth (float width) {_width  = width;}  // 横サイズセット
void NonePersProjMat::SetHeight(float height){_height = height;} // 縦サイズ比セット

NonePersProjMat::NonePersProjMat(){}
NonePersProjMat::~NonePersProjMat(){}