#pragma once

#include"I_VerticesFactory.h"
#include"B_PieceVerticesFactory.h"

class BishopVerticesFactory : public I_VerticesFactory, public B_PieceVerticesFactory
{
public:
    std::unique_ptr<Vertices> CreateVertices() override; // Šp@’¸“_W‡ì¬
};