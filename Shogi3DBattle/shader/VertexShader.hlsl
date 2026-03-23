#include"Shader.hlsli"

Output VShader(
    float4 pos    : POSITION,
    float4 normal : NORMAL,
    float2 uv     : TEXCOORD,
    uint   objId  : OBJECT_INDEX,
    uint   texId : TEXTURE_INDEX)
{
    Output output;
    
    output.svpos  = mul(viewProjMat, mul(worldMat[objId], pos));
    output.normal = mul(worldMat[objId], normal);
    output.uv     = uv;
    output.texId  = texId;
    
    return output;
}