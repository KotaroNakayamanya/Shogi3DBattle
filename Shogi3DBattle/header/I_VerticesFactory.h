#pragma once

#include"Vertices.h"
#include<memory>

class I_VerticesFactory
{
public:
    virtual std::unique_ptr<Vertices> CreateVertices() = 0; // ’¸“_W‡ì¬

    virtual ~I_VerticesFactory() = default;
};