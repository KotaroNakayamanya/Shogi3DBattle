#pragma once

#include"B_PieceVerticesFactory.h"

class RookVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // ”ò@’¸“_W‡ì¬
};