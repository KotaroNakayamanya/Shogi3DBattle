#pragma once

#include"B_PieceVerticesFactory.h"

class BishopVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // Šp@’¸“_W‡ì¬
};