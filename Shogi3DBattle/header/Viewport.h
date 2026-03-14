#pragma once

#include<d3d12.h>
#include"GameWindow.h"

class Viewport
{
private:
    D3D12_VIEWPORT _viewport; // ビューポート

public:
    void SetViewport(GameWindow* gameWindow); // ビューポートセット
    D3D12_VIEWPORT  GetViewport(); // ビューポートを返す

    Viewport();
    ~Viewport();
};