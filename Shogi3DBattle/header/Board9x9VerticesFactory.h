#pragma once

#include"B_BoardVerticesFactory.h"

class Board9x9VerticesFactory : public B_BoardVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // 9x9«Šû”Õ’¸“_W‡ì¬
};