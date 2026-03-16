#include"Shader.hlsli"

float4 PShader(Output input) : SV_Target
{
    //return float4(1, 1, 1, 1);
    //return float4(tex.Sample(samp, input.uv));
    
    //float2 aaa = { 0.99f, 0.0f };
    //float4 color = float4(tex.Sample(samp, aaa));
    //float light = 0.9f;
    //float4 finalColor = color * light;
    
    //return finalColor;
    
    return float4(input.normal.xyz, 1);
}