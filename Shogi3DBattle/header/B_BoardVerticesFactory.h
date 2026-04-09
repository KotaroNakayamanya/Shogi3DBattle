#pragma once

#include"B_VerticesFactory.h"

class B_BoardVerticesFactory : public B_VerticesFactory
{
protected:
    std::unique_ptr<I_Vertices> CreateBoardVertices(float size); // 指定されたサイズの将棋盤頂点集合作成

public:
    virtual std::unique_ptr<I_Vertices> CreateVertices() = 0; // 将棋盤頂点集合作成
};