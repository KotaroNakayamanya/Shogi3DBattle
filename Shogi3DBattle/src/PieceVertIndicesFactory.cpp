#include"PieceVertIndicesFactory.h"

// 駒の頂点インデックス集合作成
void PieceVertIndicesFactory::CreateVertIndices(NaturalBufferedData<unsigned short>* bufferedData)
{
    std::vector<unsigned short> vertIndices;

    // 表面と裏面は(0 1 2), (2 3 0), (3 4 0)で作れる
    for (int i = 0; i < 2; i++)
    {
        vertIndices.push_back(0 + 5*i);
        vertIndices.push_back(1 + 5*i);
        vertIndices.push_back(2 + 5*i);

        vertIndices.push_back(2 + 5*i);
        vertIndices.push_back(3 + 5*i);
        vertIndices.push_back(0 + 5*i);

        vertIndices.push_back(3 + 5*i);
        vertIndices.push_back(4 + 5*i);
        vertIndices.push_back(0 + 5*i);
    }

    // 側面5面は(0 1 2), (2 3 0)で作れる
    for (int i = 0; i < 5; i++)
    {
        int offset = 10; // 表面裏面の頂点数のオフセットを取得

        vertIndices.push_back(0 + offset + 4*i);
        vertIndices.push_back(1 + offset + 4*i);
        vertIndices.push_back(2 + offset + 4*i);

        vertIndices.push_back(2 + offset + 4*i);
        vertIndices.push_back(3 + offset + 4*i);
        vertIndices.push_back(0 + offset + 4*i);
    }

    bufferedData->SetDatas(vertIndices);
}