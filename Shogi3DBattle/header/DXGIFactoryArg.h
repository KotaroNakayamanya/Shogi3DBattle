#pragma once

#include<Windows.h>
#include<d3d12.h>

class DXGIFactoryArg
{
public:
    typedef struct CreateSwapChainArg
    {
        ID3D12CommandQueue* commandQueue;
        HWND hwnd;
        UINT windowWidth;
        UINT windowHeight;
        UINT rtBuffNum;

    }CreateSwapChainArg;
};