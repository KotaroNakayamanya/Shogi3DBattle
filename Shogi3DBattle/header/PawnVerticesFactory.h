#pragma once

#include"B_PieceVerticesFactory.h"

class PawnVerticesFactory : public B_PieceVerticesFactory
{
public:
    std::unique_ptr<I_Vertices> CreateVertices() override; // â§Å@í∏ì_èWçáçÏê¨
};