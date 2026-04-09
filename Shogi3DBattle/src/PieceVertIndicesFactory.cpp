#include"PieceVertIndicesFactory.h"
#include"B_NaturalBufferedData.h"
#include<vector>

// 駒のインデックス集合作成
std::unique_ptr<I_BufferedData> PieceVertIndicesFactory::CreateUniquePtr()
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
    
    B_NaturalBufferedData<unsigned short>* vertIndicesPtr = new B_NaturalBufferedData<unsigned short>();
    vertIndicesPtr->SetDatas(vertIndices);
    std::unique_ptr<I_BufferedData> uniquePtr(vertIndicesPtr);

    return uniquePtr;
}