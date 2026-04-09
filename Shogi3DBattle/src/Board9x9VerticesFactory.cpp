#include"Board9x9VerticesFactory.h"
#include"Vertices.h"
#include"GameObjIdManager.h"
#include"BasicTexType.h"
#include"GameObjType.h"

// 9x9«Šû”Õ’¸“_W‡ì¬
std::unique_ptr<Vertices> Board9x9VerticesFactory::CreateVertices()
{
    float size = 100.0f;
    return CreateBoardVertices(size);
}