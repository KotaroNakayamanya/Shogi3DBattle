#pragma once

#include<wrl.h>
#include<memory>
#include"IHeapProp.h"
#include"IResourceDesc.h"
#include"IResourceStates.h"

class I_BuffFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
    std::unique_ptr<IHeapProp>       _heapProp;      // ヒーププロパティ
    std::unique_ptr<IResourceDesc>   _resourceDesc;  // リソースディスクリプタ
    std::unique_ptr<IResourceStates> _resourceStates; // リソースステート

public:
    // バッファ作成
    virtual ComPtr<ID3D12Resource> CreateBuff(UINT widht, UINT height, ID3D12Device* device) = 0;

    virtual ~I_BuffFactory() = default;
};