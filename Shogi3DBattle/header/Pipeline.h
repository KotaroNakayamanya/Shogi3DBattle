#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

class Pipeline
{
    friend class Device; // Direct3Dデバイスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    ComPtr<ID3D12PipelineState> _pipelineState; //パイプラインステート

public:
    ID3D12PipelineState* GetPipelineState(); // パイプラインステートを渡す

    Pipeline();
    ~Pipeline();
};