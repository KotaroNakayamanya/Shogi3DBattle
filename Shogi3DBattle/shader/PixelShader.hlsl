#include"Shader.hlsli"

float4 PShader(Output input) : SV_TARGET
{
    return float4(tex.Sample(samp, input.uv));
}