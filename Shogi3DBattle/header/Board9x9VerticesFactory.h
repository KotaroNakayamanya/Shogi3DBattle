#pragma once

#include"I_VerticesFactory.h"
#include"B_BoardVerticesFactory.h"

class Board9x9VerticesFactory : public I_VerticesFactory, public B_BoardVerticesFactory
{
public:
    std::unique_ptr<Vertices> CreateVertices() override; // 9x9«Šû”Õ’¸“_W‡ì¬
};