#include"Shader.hlsli"

Output VShader(
    float4 pos    : POSITION,
    float4 normal : NORMAL,
    float2 uv     : TEXCOORD)
{
    Output output;
    
    output.svpos = mul(mat, pos);
    output.normal = normal;
    output.uv = uv;
    
    return output;
}