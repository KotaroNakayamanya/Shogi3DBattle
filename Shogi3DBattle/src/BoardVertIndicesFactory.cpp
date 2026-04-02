#include"BoardVertIndicesFactory.h"

// 将棋盤頂点インデックス集合作成
void BoardVertIndicesFactory::CreateVertIndices(BufferedData<unsigned short>* bufferedData)
{
    std::vector<unsigned short> vertIndices;

    // (0 1 2) (2 3 0)を５面で作れる
    for (int i = 0; i < 5; i++)
    {
        unsigned int offset = 4 * i;

        vertIndices.push_back(0 + offset);
        vertIndices.push_back(1 + offset);
        vertIndices.push_back(2 + offset);

        vertIndices.push_back(2 + offset);
        vertIndices.push_back(3 + offset);
        vertIndices.push_back(0 + offset);
    }

    bufferedData->SetDatas(vertIndices);
}