#include"Shader.hlsli"

Output VShader(
    float4 pos : POSITION,
    float2 uv  : TEXCOORD)
{
    Output output;
    
    output.pos = mul(mat, pos);
    output.uv = uv;
    
    return output;
}