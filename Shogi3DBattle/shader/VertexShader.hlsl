#include"Shader.hlsli"

Output VShader(
    float4 position : POSITION,
    float2 uv       : TEXCOORD)
{
    Output output;
    
    output.svPosition = position;
    output.uv = uv;
    
    return output;
}