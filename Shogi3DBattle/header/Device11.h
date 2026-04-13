#pragma once

#include<d3d11on12.h>
#include<memory>
#include"D2DDeviceContext.h"

class Device11
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11On12Device> _device11;

public:
    // Direct2Dデバイスコンテキスト作成
    HRESULT CreateD2DDeviceContext(D2DDeviceContext* d2dDeviceContext);
    // ラップされたバックバッファ作成
    ComPtr<ID3D11Resource> CreateWrappedBackBuff(ID3D12Resource* buff);
    // ラップされたテクスチャバッファ作成
    ComPtr<ID3D11Resource> CreateWrappedTexBuff(ID3D12Resource* buff);

    // ラップされたバッファへのレンダリングを許可
    void AcquireWrappedBuff(ID3D11Resource** wrappedBuffAddress);
    // ラップされたバッファへのレンダリングをリリース
    void ReleaseWrappedBuff(ID3D11Resource** wrappedBuffAddress);

    void SetDevice11(ComPtr<ID3D11On12Device> device11); // Direct3D11デバイスセット

    Device11();
    ~Device11();
};