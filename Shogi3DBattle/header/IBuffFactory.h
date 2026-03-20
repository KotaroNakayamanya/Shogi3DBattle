#pragma once

#include"Buff.h"
#include<memory>
#include"IHeapProp.h"
#include"IResourceDesc.h"
#include"IResourceStates.h"

class IBuffFactory
{
protected:
    std::unique_ptr<IHeapProp>       _heapProp;      // ヒーププロパティ
    std::unique_ptr<IResourceDesc>   _resourceDesc;  // リソースディスクリプタ
    std::unique_ptr<IResourceStates> _resourceStates; // リソースステート

public:
    // バッファ作成
    virtual HRESULT CreateBuff(Buff* buff, UINT widht, UINT height, ID3D12Device* device) = 0;

    IBuffFactory() = default;
    ~IBuffFactory(){}
};