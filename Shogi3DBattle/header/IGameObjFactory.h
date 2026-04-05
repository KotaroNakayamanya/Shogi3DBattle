#pragma once

#include"GameObj.h"
#include"IBufferedDataFactory.h"
#include"VertStruct.h"

class IGameObjFactory
{
protected:
    std::unique_ptr<IBufferedDataFactory<Vert>>              _verticesFactory; // 頂点集合ファクトリー
    std::unique_ptr<IBufferedDataFactory<DirectX::XMMATRIX>> _matFactory;      // 行列ファクトリー

public:
    virtual std::unique_ptr<GameObj> CreateUniquePtr() = 0; // ゲームオブジェクト作成

    virtual ~IGameObjFactory() = default;
};