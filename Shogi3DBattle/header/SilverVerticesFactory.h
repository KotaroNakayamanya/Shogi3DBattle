#pragma once

#include"B_PieceVerticesFactory.h"

class SilverVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // ‹â@’¸“_W‡ì¬
};