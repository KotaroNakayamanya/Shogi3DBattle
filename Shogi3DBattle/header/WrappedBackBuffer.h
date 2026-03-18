#pragma once

#include<d3d11on12.h>
#include<wrl.h>

class WrappedBackBuffer
{
    friend class Device11;
    friend class D2DDeviceContext;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11Resource> _wrappedBackBuffer;

public:
    WrappedBackBuffer(){}
    ~WrappedBackBuffer(){}
};