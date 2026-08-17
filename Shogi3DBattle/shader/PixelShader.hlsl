#include"Shader.hlsli"

float4 PShader(Output input) : SV_Target
{
    float4 basicTex  = basicTexs [input.basicTexId] .Sample(samp, input.uv);
    float4 designTex = designTexs[input.designTexId].Sample(samp, input.uv);
    float4 effectTex = effectTexs[input.effectTexId].Sample(samp, input.uv);
    
    float4 light = normalize(float4(0, 0.5, 1, 0));
    float1 lightEffect = -dot(light, input.normal);
    
    float1 finalLight = max(lightEffect, 0.6f);
    
    
    
    // return basicTex; // 基本色のみ

    // designTex = designTexs[input.designTexId+3].Sample(samp, input.uv);
    // return designTex; // オブジェクトごとの文字等のみ

    // effectTex = effectTexs[input.effectTexId+14].Sample(samp, input.uv);
    // return effectTex; // エフェクトのみ


    // return finalLight; // 光のみ

    return basicTex * designTex * effectTex * finalLight; // 全部
}