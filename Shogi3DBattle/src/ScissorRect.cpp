#include"ScissorRect.h"

void ScissorRect::SetScissorRect(GameWindow* gameWindow)
{
    _scissorRect.left   = 0;                             // 左
    _scissorRect.right  = gameWindow->GetWindowWidth();  // 右
    _scissorRect.top    = 0;                             // 上
    _scissorRect.bottom = gameWindow->GetWindowHeight(); // 下
}

D3D12_RECT ScissorRect::GetScissorRect(){return _scissorRect;} // シザー矩形を返す

ScissorRect::ScissorRect(){}
ScissorRect::~ScissorRect(){}