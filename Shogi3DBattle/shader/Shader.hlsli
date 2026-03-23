struct Output
{
    float4 svpos  : SV_POSITION;
    float4 normal : NORMAL;
    float2 uv     : TEXCOORD;
};



//Texture2D<float4> tex: register(t1);
//Texture2D<float4> tex : register(t0);



Texture2D<float4> tex : register(t0);
Texture2D<float4> boardLineTex[1] : register(t1);

SamplerState samp : register(s0); // 0番　サンプラー

cbuffer cbuff : register(b0) // 0番　定数バッファ
{
    matrix worldMat[41];
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