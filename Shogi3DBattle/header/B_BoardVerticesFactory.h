#pragma once

#include"Vertices.h"
#include<memory>

class B_BoardVerticesFactory
{
protected:
    std::unique_ptr<Vertices> CreateBoardVertices(float size); // 指定されたサイズの将棋盤頂点集合作成
};