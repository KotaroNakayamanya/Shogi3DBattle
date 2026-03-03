#include"Shader.hlsli"

float4 PShader(Output input) : SV_TARGET
{
    return float4(0.85f, 0.7f, 0.5f, 1);
}