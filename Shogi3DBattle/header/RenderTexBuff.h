#pragma once

#include<d3d12.h>
#include<wrl.h>

class RenderTexBuff
{
    friend class Device;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _renderTexBuff;

public:
    

    RenderTexBuff();
    ~RenderTexBuff();
};