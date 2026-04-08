#include"BoardVertIndicesFactory.h"
#include"NaturalBufferedData.h"

// 将棋盤インデックス集合作成
std::unique_ptr<BufferedData> BoardVertIndicesFactory::CreateUniquePtr()
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
    
    NaturalBufferedData<unsigned short>* vertIndicesPtr = new NaturalBufferedData<unsigned short>();
    vertIndicesPtr->SetDatas(vertIndices);
    std::unique_ptr<BufferedData> vertIndicesUniquePtr(vertIndicesPtr);

    return vertIndicesUniquePtr;
}