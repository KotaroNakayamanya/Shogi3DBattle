#include"Shader.hlsli"

Output VShader(
    float4 pos    : POSITION,
    float4 normal : NORMAL,
    float2 uv     : TEXCOORD)
{
    Output output;
    
    output.svpos = mul(viewProjMat, mul(worldMat, pos));
    output.normal = mul(worldMat, normal);
    output.uv = uv;
    
    return output;
}