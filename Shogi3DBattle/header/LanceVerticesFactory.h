#pragma once

#include"B_PieceVerticesFactory.h"

class LanceVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // @’¸“_W‡ì¬
};