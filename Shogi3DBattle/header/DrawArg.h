#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>

class DXGIFactory;


class DrawArg
{
public:
    // 描画オブジェクト作成用引数
    typedef struct CreateDrawObjArg
    {
        ID3D12Device*  device;
        DXGIFactory* dxgiFactoryObj;
        HWND hwnd;
        UINT windowWidth;
        UINT windowHeight;
        UINT buffNum;

    }CreateDrawObjArg;

    // コマンドセット用引数
    typedef struct SetCommandArg
    {
        ID3D12PipelineState* pipelineState;
        ID3D12RootSignature* rootSignature;
        ID3D12DescriptorHeap* csuHeap;
        UINT offset;

        D3D12_PRIMITIVE_TOPOLOGY topology;
        D3D12_VERTEX_BUFFER_VIEW vertexBuffView;
        D3D12_INDEX_BUFFER_VIEW  indexBuffView;

        UINT vertexCount;
        UINT objCount;

    }SetCommandArg;

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