#include"Viewport.h"

void Viewport::SetViewport(GameWindow* gameWindow)
{
    _viewport.TopLeftX = 0; // 左上横位置
    _viewport.TopLeftY = 0; // 左上縦位置
    _viewport.Width    = gameWindow->GetWindowWidth();  // 横
    _viewport.Height   = gameWindow->GetWindowHeight(); // 縦
    _viewport.MaxDepth = 1.0f; // 深度最大値
    _viewport.MinDepth = 0.0f; // 深度最小値
}

D3D12_VIEWPORT Viewport::GetViewport(){return _viewport;} // ビューポートを返す

Viewport::Viewport(){}
Viewport::~Viewport(){}