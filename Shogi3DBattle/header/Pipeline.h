#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<vector>

#include"PipelineArg.h"

class Pipeline
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
    ComPtr<ID3D12PipelineState> _pipelineState; //パイプラインステート

    D3D12_GRAPHICS_PIPELINE_STATE_DESC GetPipelineStateDesc( // パイプラインステートディスクリプタ
        ID3D12RootSignature* rootSignature,
        ID3DBlob* vertexShaderBlob,
        ID3DBlob* pixelShaderBlob,
        DXGI_SAMPLE_DESC sampleDesc); 
    D3D12_SHADER_BYTECODE GetVertexShaderDesc( // 頂点シェーダーディスクリプタ
        ID3DBlob* vertexShaderBlob);
    D3D12_SHADER_BYTECODE GetPixelShaderDesc(  // ピクセルシェーダーディスクリプタ
        ID3DBlob* pixelShaderBlob);
    D3D12_BLEND_DESC GetBlendStateDesc();                      // ブレンドステートディスクリプタ
    D3D12_RENDER_TARGET_BLEND_DESC GetRenderTargetBlendDesc(); // レンダーターゲットブレンドディスクリプタ
    D3D12_RASTERIZER_DESC GetRasterizerDesc();                 // ラスタライザディスクリプタ
    D3D12_INPUT_LAYOUT_DESC GetInputLayoutDesc(                // インプットレイアウトディスクリプタ
        std::vector<D3D12_INPUT_ELEMENT_DESC>& inputLayout);


public:
    HRESULT CreatePipelineState(PipelineArg::CreatePipelineStateArg arg); // パイプラインステート作成
    ID3D12PipelineState* GetPipelineState(); // パイプラインステートを渡す

    Pipeline();
    ~Pipeline();
};