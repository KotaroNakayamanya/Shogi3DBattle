#pragma once

#include"I_VerticesFactory.h"
#include"B_PieceVerticesFactory.h"

class RookVerticesFactory : public I_VerticesFactory, public B_PieceVerticesFactory
{
public:
    std::unique_ptr<Vertices> CreateVertices() override; // ”ò@’¸“_W‡ì¬
};