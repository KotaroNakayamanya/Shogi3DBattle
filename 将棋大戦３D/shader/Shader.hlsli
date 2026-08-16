struct Output
{
    float4 svpos        : SV_POSITION;
    float4 normal       : NORMAL;
    float2 uv           : TEXCOORD;
    uint   basicTexId   : BASIC_TEXTURE_INDEX;
    uint   designTexId  : DESIGN_TEXTURE_INDEX;
    uint   effectTexId  : EFFECT_TEXTURE_INDEX;
};

tbuffer tbuff : register(t0)
{
    Texture2D<float4> basicTexs [3];
    Texture2D<float4> designTexs[11];
    Texture2D<float4> effectTexs[2];
}

SamplerState samp : register(s0); // 0番　サンプラー

cbuffer cbuff : register(b0) // 0番　定数バッファ
{
    matrix worldMat[43];
    matrix viewProjMat;
}
