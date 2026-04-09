#pragma once

#include"B_PieceVerticesFactory.h"

class GoldVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // ‹à@’¸“_W‡ì¬
};