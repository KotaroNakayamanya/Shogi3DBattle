#include"BoardVertIndicesFactory.h"
#include"VertIndices.h"

// 将棋盤インデックス集合作成
std::unique_ptr<I_BufferedData> BoardVertIndicesFactory::CreateUniquePtr()
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
    
    std::unique_ptr<VertIndices> uniquePtr = std::make_unique<VertIndices>();
    uniquePtr->SetDatas(vertIndices);
    return uniquePtr;
    
}