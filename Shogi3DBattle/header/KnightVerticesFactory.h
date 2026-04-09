#pragma once

#include"B_PieceVerticesFactory.h"

class KnightVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // Œj@’¸“_W‡ì¬
};