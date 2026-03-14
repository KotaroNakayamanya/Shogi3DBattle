#pragma once

#include<d3d12.h>
#include"GameWindow.h"

class ScissorRect
{
private:
    D3D12_RECT _scissorRect; // シザー矩形
public:
    void SetScissorRect(GameWindow* gameWindow); // シザー矩形セット
    D3D12_RECT GetScissorRect(); // シザー矩形を返す

    ScissorRect();
    ~ScissorRect();
};