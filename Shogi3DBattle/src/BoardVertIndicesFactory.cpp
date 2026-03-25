#include"BoardVertIndicesFactory.h"

// 将棋盤頂点インデックス集合作成
void BoardVertIndicesFactory::CreateVertIndices(VertIndices* vertIndices)
{
    std::vector<USHORT> tempVertIndices;

    // (0 1 2) (2 3 0)を５面で作れる
    for (UINT i = 0; i < 5; i++)
    {
        UINT offset = 4 * i;

        tempVertIndices.push_back(0 + offset);
        tempVertIndices.push_back(1 + offset);
        tempVertIndices.push_back(2 + offset);

        tempVertIndices.push_back(2 + offset);
        tempVertIndices.push_back(3 + offset);
        tempVertIndices.push_back(0 + offset);
    }

    vertIndices->SetVertIndices(tempVertIndices);
}

BoardVertIndicesFactory::BoardVertIndicesFactory(){}
BoardVertIndicesFactory::~BoardVertIndicesFactory(){}