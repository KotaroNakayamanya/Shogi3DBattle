#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>

class DrawArg
{
public:
    // 描画オブジェクト作成用引数
    typedef struct CreateDrawObjArg
    {
        ID3D12Device*  device;
        IDXGIFactory6* dxgiFactory;
        HWND hwnd;

    }CreateDrawObjArg;

    // レンダーターゲット準備用引数
    typedef struct PrepareRenderTargetArg
    {
        UINT rtvOffset;
        D3D12_RESOURCE_BARRIER resourceBarrier;

    }PrepareRenderTargetArg;

    // コマンドセット用引数
    typedef struct SetCommandArg
    {
        ID3D12PipelineState* pipelineState;
        ID3D12RootSignature* rootSignature;
        ID3D12DescriptorHeap* heap;
        UINT offset;

        D3D12_VIEWPORT viewport;
        D3D12_RECT     scissorRect;

        D3D12_PRIMITIVE_TOPOLOGY topology;
        D3D12_VERTEX_BUFFER_VIEW vertexBuffView;
        D3D12_INDEX_BUFFER_VIEW  indexBuffView;

        UINT vertexCount;
        UINT objCount;

    }SetCommandArg;

    // コマンド実行用引数
    typedef struct ExeDrawArg
    {
        D3D12_RESOURCE_BARRIER resourceBarrier;

    }ExeDrawArg;

    // スワップチェーン作成用引数
    typedef struct CreateSwapChainArg
    {
        IDXGIFactory6* dxgiFactory;
        ID3D12CommandQueue* commandQueue;
        HWND hwnd;
        UINT width;
        UINT height;
        UINT buffNum;

    }CreateSwapChainArg;

    DrawArg(){}
    ~DrawArg(){}
};