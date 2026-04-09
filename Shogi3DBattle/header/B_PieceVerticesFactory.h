#pragma once

#include"B_VerticesFactory.h"

class B_PieceVerticesFactory : public B_VerticesFactory
{
protected:
    std::unique_ptr<I_Vertices> CreatePieceVertices(float mmBottomWidth, float mmHeight); // 指定されたサイズの駒の頂点集合作成

public:
    virtual std::unique_ptr<I_Vertices> CreateVertices() = 0; // 駒の頂点集合作成
};