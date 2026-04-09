#pragma once

#include"I_VerticesFactory.h"

class B_VerticesFactory : public I_VerticesFactory
{
public:
    virtual std::unique_ptr<I_Vertices> CreateVertices() = 0; // ’¸“_W‡ì¬
};