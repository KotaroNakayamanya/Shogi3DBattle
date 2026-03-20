#pragma once

#include<d3d11on12.h>
#include<memory>
#include"D2DDeviceContext.h"
#include"WrappedBackBuff.h"
#include"BackBuff.h"

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
    HRESULT CreateWrappedBackBuff(WrappedBackBuff* wrappedBackBuff, BackBuff* backBuff);

    // ラップされたバックバッファへのレンダリングを許可
    void AcquireWrappedBackBuff(WrappedBackBuff* wrappedBackBuff);
    // ラップされたバックバッファへのレンダリングをリリース
    void ReleaseWrappedBackBuff(WrappedBackBuff* wrappedBackBuff);

    void SetDevice11(ComPtr<ID3D11On12Device> device11); // Direct3D11デバイスセット

    Device11();
    ~Device11();
};