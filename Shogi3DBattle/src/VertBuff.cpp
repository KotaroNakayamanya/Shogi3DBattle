#include"VertBuff.h"

//HRESULT VertBuff::WriteToBuff(Vertices* verticesObj, UINT idx)
//{
//    Vertices::Vert* vertBuffMap;
//
//    HRESULT result = _buff->Map(0, nullptr, (void**)&vertBuffMap);
//    if (FAILED(result)) return result;
//
//    vertBuffMap += idx;
//
//    auto vertices = verticesObj->GetVertices();
//
//    std::copy(vertices.begin(), vertices.end(), vertBuffMap);
//
//    _buff->Unmap(0, nullptr);
//}
HRESULT VertBuff::WriteToBuff(GameObj* gameObj, UINT idx)
{
    GameObj::Vert* vertBuffMap;

    HRESULT result = _buff->Map(0, nullptr, (void**)&vertBuffMap);
    if (FAILED(result)) return result;

    vertBuffMap += idx;

    auto vertices = gameObj->GetVertices();

    std::copy(vertices.begin(), vertices.end(), vertBuffMap);

    _buff->Unmap(0, nullptr);
}

VertBuff::VertBuff() {}
VertBuff::~VertBuff() {}