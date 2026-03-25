#pragma once

#include"IVertIndicesFactory.h"

class BoardVertIndicesFactory : public IVertIndicesFactory
{
public:
    // 将棋盤頂点インデックス集合作成
    void CreateVertIndices(VertIndices* vertIndices) override;

    BoardVertIndicesFactory();
    ~BoardVertIndicesFactory();
};