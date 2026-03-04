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

        D3D12_COMMAND_QUEUE_DESC   commandQueueDesc;
        DXGI_SWAP_CHAIN_DESC1      swapChainDesc;
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;

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
        ID3D12DescriptorHeap* textureDescHeap;


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
};