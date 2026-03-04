#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>

class DrawArgument
{
public:
    // 描画オブジェクト作成用引数
    typedef struct CreateDrawObjectArgument
    {
        ID3D12Device*  device;
        IDXGIFactory6* dxgiFactory;

        HWND hwnd;

        D3D12_COMMAND_QUEUE_DESC   commandQueueDesc;
        DXGI_SWAP_CHAIN_DESC1      swapChainDesc;
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;

    }CreateDrawObjectArgument;

    // レンダーターゲット準備用引数
    typedef struct PrepareRenderTargetArgument
    {
        UINT rtvOffset;
        D3D12_RESOURCE_BARRIER resourceBarrier;
    };

    // コマンドセット用引数
    typedef struct SetCommandArgument
    {
        ID3D12PipelineState* pipelineState;
        ID3D12RootSignature* rootSignature;
        ID3D12DescriptorHeap* textureDescHeap;


        D3D12_VIEWPORT viewport;
        D3D12_RECT     scissorRect;

        D3D12_PRIMITIVE_TOPOLOGY topology;
        D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
        D3D12_INDEX_BUFFER_VIEW  indexBufferView;

        UINT vertexCount;
        UINT objectCount;

    }SetCommandArgument;

    // コマンド実行用引数
    typedef struct ExecuteDrawArgument
    {
        D3D12_RESOURCE_BARRIER resourceBarrier;

    }ExecuteDrawArgument;
};