#include"Shader.hlsli"

float4 PShader(Output input) : SV_Target
{
    //return float4(input.uv, 1, 1);
    //return float4(1, 1, 1, 1);
    //float4 aaa = 
    
    float4 wood      = tex.Sample(samp, input.uv);
    float4 draw = drawTex[input.texId].Sample(samp, input.uv);
    //float4 boardLine = drawTex[1].Sample(samp, input.uv);
    
    
    return wood * draw;
    
    //float2 aaa = { 0.5f, 0.0f };
    //float4 color = float4(tex.Sample(samp, aaa));
    //float light = 0.9f;
    //float4 finalColor = color * light;
    
    //return finalColor;
    
    //return float4(input.normal.xyz, 1);
}