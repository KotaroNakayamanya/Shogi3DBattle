#include"Shader.hlsli"

float4 PShader(Output input) : SV_Target
{
    //return float4(input.normal);
    
    //return float4(input.uv, 1, 1);
    
    float4 basicTex  = basicTexs [input.basicTexId] .Sample(samp, input.uv);
    float4 designTex = designTexs[input.designTexId].Sample(samp, input.uv);
    float4 effectTex = effectTexs[input.effectTexId].Sample(samp, input.uv);
    
    float4 light = normalize(float4(0, 0.5, 1, 0));
    float1 lightEffect = -dot(light, input.normal);
    
    float1 finalLight = max(lightEffect, 0.6f);
    
    
    //float4 shogiObjTex = drawTex[8].Sample(samp, input.uv);
    
    return basicTex * designTex * effectTex * finalLight;
    //return basicTex * designTex  * finalLight;
}