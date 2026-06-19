#include"CubeVertIndices.h"

CubeVertIndices::CubeVertIndices()
{
    // 将棋盤のインデックス集合作成
    std::vector<unsigned short> vertIndices;

    // (0 1 2) (2 3 0)を6面で作れる
    for (int i = 0; i < 6; i++)
    {
        unsigned int offset = 4 * i;

        vertIndices.push_back(0 + offset);
        vertIndices.push_back(1 + offset);
        vertIndices.push_back(2 + offset);

        vertIndices.push_back(2 + offset);
        vertIndices.push_back(3 + offset);
        vertIndices.push_back(0 + offset);
    }

    SetDatas(vertIndices);
}