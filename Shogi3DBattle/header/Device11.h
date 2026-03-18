#pragma once

#include<d3d11on12.h>
#include<memory>
#include"D2DDeviceContext.h"
#include"WrappedBackBuffer.h"
#include"BackBuff.h"

class Device11
{
    friend class Device;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D11On12Device> _device11;

public:
    // Direct2Dデバイスコンテキスト作成
    HRESULT CreateD2DDeviceContext(D2DDeviceContext* d2dDeviceContext);
    // ラップされたバックバッファ作成
    HRESULT CreateWrappedBackBuffer(WrappedBackBuffer* wrappedBackBuffer, BackBuff* backBuff);

    // ラップされたバックバッファへのレンダリングを許可
    void AcquireWrappedBackBuffer(WrappedBackBuffer* wrappedBackBuffer);
    // ラップされたバックバッファへのレンダリングをリリース
    void ReleaseWrappedBackBuffer(WrappedBackBuffer* wrappedBackBuffer);

    Device11();
    ~Device11();
};