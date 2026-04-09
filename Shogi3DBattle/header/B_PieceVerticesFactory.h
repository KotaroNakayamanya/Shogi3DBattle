#pragma once

#include"Vertices.h"
#include<memory>

class B_PieceVerticesFactory
{
protected:
    std::unique_ptr<Vertices> CreatePieceVertices(float mmBottomWidth, float mmHeight); // 指定されたサイズの駒の頂点集合作成
};