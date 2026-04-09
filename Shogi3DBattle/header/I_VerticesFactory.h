#pragma once

#include"I_Vertices.h"
#include<memory>

class I_VerticesFactory
{
public:
    virtual std::unique_ptr<I_Vertices> CreateVertices() = 0; // ’¸“_W‡ì¬

    virtual ~I_VerticesFactory() = default;
};