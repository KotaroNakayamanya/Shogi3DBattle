#include"Shader.hlsli"

Output VShader(
    float4 pos    : POSITION,
    float4 normal : NORMAL,
    float2 uv     : TEXCOORD,
    uint   objId       : OBJECT_INDEX,
    uint   basicTexId  : BASIC_TEXTURE_INDEX,
    uint   designTexId : DESIGN_TEXTURE_INDEX,
    uint   effectTexId : EFFECT_TEXTURE_INDEX)
{
    Output output;
    
    // 座標変換後の座標
    output.svpos  = mul(viewProjMat, mul(worldMat[objId], pos));
    
    // 法線 平行移動成分は0にする
    float4 normal_w0 = normal;
    normal_w0.w = 0;
    float4 noneNormalizedNormal = mul(worldMat[objId], normal_w0);
    output.normal = normalize(noneNormalizedNormal);
    
    output.uv     = uv;
    output.basicTexId   = basicTexId;
    output.designTexId  = designTexId;
    output.effectTexId = effectTexId;
    
    return output;
}