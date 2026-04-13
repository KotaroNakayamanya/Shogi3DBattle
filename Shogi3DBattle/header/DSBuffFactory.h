#pragma once

#include"I_BuffFactory.h"

class DSBuffFactory : public I_BuffFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
    // デプスステンシルバッファ作成
    ComPtr<ID3D12Resource> CreateBuff(UINT widht, UINT height, ID3D12Device* device) override;

    DSBuffFactory ();
};