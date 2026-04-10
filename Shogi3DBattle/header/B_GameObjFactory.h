#pragma once

#include"I_VerticesFactory.h"

class B_GameObjFactory
{
protected:
    std::unique_ptr<I_VerticesFactory> _verticesFactory; // 頂点集合ファクトリー
};