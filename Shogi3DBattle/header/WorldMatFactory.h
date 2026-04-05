#pragma once

#include"IBufferedDataFactory.h"
#include<DirectXMath.h>

class WorldMatFactory : public IBufferedDataFactory<DirectX::XMMATRIX>
{
public:
    std::unique_ptr<BufferedData<DirectX::XMMATRIX>> CreateUniquePtr() override; // ƒ[ƒ‹ƒhs—ñì¬
};