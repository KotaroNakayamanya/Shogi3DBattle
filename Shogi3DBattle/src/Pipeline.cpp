#include"Pipeline.h"

// パイプラインステート作成
HRESULT Pipeline::CreatePipelineState(PipelineArg::CreatePipelineStateArg arg)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc =
        GetPipelineStateDesc(
            arg.rootSignature,
            arg.vertexShaderBlob,
            arg.pixelShaderBlob,
            arg.sampleDesc);

    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
    inputLayout.resize(2);
    inputLayout[0] =
    { // 頂点レイアウト
        "POSITION",
        0,
        DXGI_FORMAT_R32G32B32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };
    inputLayout[1] = 
    { // uv
        "TEXCOORD",
        0,
        DXGI_FORMAT_R32G32_FLOAT,
        0,
        D3D12_APPEND_ALIGNED_ELEMENT,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
        0
    };

    D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
    inputLayoutDesc.pInputElementDescs =
        inputLayout.data();
    inputLayoutDesc.NumElements =
        inputLayout.size();
    
    desc.InputLayout = inputLayoutDesc;

    return arg.device->CreateGraphicsPipelineState(
        &desc,
        IID_PPV_ARGS(_pipelineState.ReleaseAndGetAddressOf()));
}

// パイプラインステートディスクリプタ
D3D12_GRAPHICS_PIPELINE_STATE_DESC Pipeline::GetPipelineStateDesc(
    ID3D12RootSignature* rootSignature,
    ID3DBlob* vertexShaderBlob,
    ID3DBlob* pixelShaderBlob,
    DXGI_SAMPLE_DESC sampleDesc)
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};   
    
    desc.pRootSignature =
        rootSignature;
    desc.VS =
        GetVertexShaderDesc(vertexShaderBlob);
    desc.PS =
        GetPixelShaderDesc(pixelShaderBlob);
    desc.SampleMask =
        D3D12_DEFAULT_SAMPLE_MASK;
    desc.BlendState =
        GetBlendStateDesc();
    desc.RasterizerState =
        GetRasterizerDesc();
    desc.IBStripCutValue =
        D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    desc.PrimitiveTopologyType =
        D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    desc.NumRenderTargets =
        1;
    desc.RTVFormats[0] =
        DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc =
        sampleDesc;

    return desc;
}

// インプットレイアウトディスクリプタ
D3D12_INPUT_LAYOUT_DESC Pipeline::GetInputLayoutDesc(
    std::vector<D3D12_INPUT_ELEMENT_DESC>* inputLayout)
{
    D3D12_INPUT_LAYOUT_DESC desc = {};

    desc.pInputElementDescs =
        inputLayout->data();
    desc.NumElements =
        inputLayout->size();
 
    return desc;
}

// 頂点シェーダディスクリプタ
D3D12_SHADER_BYTECODE Pipeline::GetVertexShaderDesc(
    ID3DBlob* vertexShaderBlob)
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        vertexShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        vertexShaderBlob->GetBufferSize();

    return desc;
}

// ピクセルシェーダディスクリプタ
D3D12_SHADER_BYTECODE Pipeline::GetPixelShaderDesc(
    ID3DBlob* pixelShaderBlob)
{
    D3D12_SHADER_BYTECODE desc = {};

    desc.pShaderBytecode =
        pixelShaderBlob->GetBufferPointer();
    desc.BytecodeLength =
        pixelShaderBlob->GetBufferSize();

    return desc;
}

// ブレンドステートディスクリプタ
D3D12_BLEND_DESC Pipeline::GetBlendStateDesc()
{
    D3D12_BLEND_DESC desc = {};

    desc.AlphaToCoverageEnable =
        false;
    desc.IndependentBlendEnable =
        false;
    desc.RenderTarget[0] = 
        GetRenderTargetBlendDesc();

    return desc;
}

// レンダーターゲットステートディスクリプタ
D3D12_RENDER_TARGET_BLEND_DESC Pipeline::GetRenderTargetBlendDesc()
{
    D3D12_RENDER_TARGET_BLEND_DESC desc = {};

    desc.BlendEnable =
        false;
    desc.LogicOpEnable =
        false;
    desc.RenderTargetWriteMask =
        D3D12_COLOR_WRITE_ENABLE_ALL;

    return desc;
}

// ラスタライザディスクリプタ
D3D12_RASTERIZER_DESC Pipeline::GetRasterizerDesc()
{
    D3D12_RASTERIZER_DESC desc = {};

    desc.MultisampleEnable =
        false;
    desc.CullMode =
        D3D12_CULL_MODE_NONE;
    desc.FillMode =
        D3D12_FILL_MODE_SOLID;
    desc.DepthClipEnable =
        true;

    return desc;
}




// パイプラインステートを渡す
ID3D12PipelineState* Pipeline::GetPipelineState()
{
    return _pipelineState.Get();
}




Pipeline::Pipeline(){}
Pipeline::~Pipeline(){}