struct Output
{
    float4 svpos        : SV_POSITION;
    float4 normal       : NORMAL;
    float2 uv           : TEXCOORD;
    uint   basicTexId   : BASIC_TEXTURE_INDEX;
    uint   designTexId  : DESIGN_TEXTURE_INDEX;
    uint   effectTexId  : EFFECT_TEXTURE_INDEX;
};



//Texture2D<float4> tex: register(t1);
//Texture2D<float4> tex : register(t0);

tbuffer tbuff : register(t0)
{
    Texture2D<float4> basicTexs [3];
    Texture2D<float4> designTexs[11];
}



SamplerState samp : register(s0); // 0番　サンプラー

cbuffer cbuff : register(b0) // 0番　定数バッファ
{
    matrix worldMat[43];
    matrix viewProjMat;
}

//cbuffer cbuff : register(b0) // 0番　定数バッファ
//{
//    matrix worldMat2[41];
//    matrix viewProjMat2;
//}
//cbuffer cbuff : register(b0) // 0番　定数バッファ
//{
//    matrix worldMat[41];
//    matrix viewProjMat;
//}