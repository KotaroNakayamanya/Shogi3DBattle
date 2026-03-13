#pragma once

#include"Shader.h"
#include"VertBuff.h"

class Device
{
    friend class DXGIFactory; // DXGIFactoryから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Device> _device; // Direct3Dデバイス

    HRESULT CreateVShaderBlob(Shader* shaderObj); // 頂点シェーダ作成
    HRESULT CreatePShaderBlob(Shader* shaderObj);  // ピクセルシェーダ作成

    D3D12_HEAP_PROPERTIES GetHeapProp(); // 頂点ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc(UINT byteSize);  // リソースディスクリプタ

public:
    HRESULT CreateShaderObj(Shader* shaderObj); // シェーダーオブジェクト作成
    HRESULT CreateVertBuff(VertBuff* vertBuffObj, UINT byteSize); // 頂点バッファ作成

    ID3D12Device* GetDevice(); // Direct3Dデバイスを渡す

    Device();
    ~Device();
};