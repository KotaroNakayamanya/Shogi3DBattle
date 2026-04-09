#pragma once

#include"I_VerticesFactory.h"
#include"B_PieceVerticesFactory.h"

class PawnVerticesFactory : public I_VerticesFactory, public B_PieceVerticesFactory
{
public:
    std::unique_ptr<Vertices> CreateVertices() override; // â§Å@í∏ì_èWçáçÏê¨
};