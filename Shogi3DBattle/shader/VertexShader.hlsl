#include"Shader.hlsli"

Output VShader(
    float4 pos    : POSITION,
    float4 normal : NORMAL,
    float2 uv     : TEXCOORD,
    uint   idx    : INDEX)
{
    Output output;
    
    output.svpos = mul(viewProjMat, mul(worldMat[idx], pos));
    output.normal = mul(worldMat[idx], normal);
    output.uv = uv;
    
    return output;
}