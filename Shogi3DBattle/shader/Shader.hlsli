struct Output
{
    float4 svPosition : SV_POSITION;
    float2 uv         : TEXCOORD;
};

Texture2D<float4> tex : register(t0); // 0番　テクスチャ
SamplerState samp       : register(s0); // 0番　サンプラー