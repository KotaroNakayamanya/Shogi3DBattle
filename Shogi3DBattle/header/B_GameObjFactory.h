#pragma once

#include"I_VerticesFactory.h"
#include"I_WorldMatFactory.h"

class B_GameObjFactory
{
protected:
    std::unique_ptr<I_VerticesFactory> _verticesFactory; // 頂点集合ファクトリー
    std::unique_ptr<I_WorldMatFactory> _worldMatFactory; // ワールド行列ファクトリー
};