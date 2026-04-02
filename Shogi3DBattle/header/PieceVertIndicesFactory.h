#pragma once

#include"IVertIndicesFactory.h"

class PieceVertIndicesFactory : public IVertIndicesFactory
{
public:
    // 駒の頂点インデックス集合作成
    void CreateVertIndices(BufferedData<unsigned short>* bufferedData) override;
};