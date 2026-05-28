#pragma once

#include"I_Vertices.h"
#include"GameObjType.h"
#include"BasicTexType.h"

class CubeVertices : public I_Vertices
{
public:
    CubeVertices(GameObjType gameObjType, BasicTexType basicTexType, float sideLength);
};