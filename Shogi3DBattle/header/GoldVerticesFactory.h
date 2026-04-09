#pragma once

#include"I_VerticesFactory.h"
#include"B_PieceVerticesFactory.h"

class GoldVerticesFactory : public I_VerticesFactory, public B_PieceVerticesFactory
{
public:
    std::unique_ptr<Vertices> CreateVertices() override; // ã‡Å@í∏ì_èWçáçÏê¨
};