struct Output
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD;
};

Texture2D<float4> tex : register(t0); // 0番　テクスチャ
SamplerState samp     : register(s0); // 0番　サンプラー
cbuffer cbuff       : register(b0)  // 0番　定数バッファ
{
    matrix mat;
}