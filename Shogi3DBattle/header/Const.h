#pragma once

#include<d3d12.h>
#include<DirectXMath.h>
#include<wrl.h>

class Const
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _buff; // コンスタントバッファ
    DirectX::XMMATRIX* _mappedMat; // バッファを指す行列

    HRESULT CreateBuff(ID3D12Device* device); // コンスタントバッファ作成
    HRESULT MapBuff(); // バッファにマップ

    D3D12_HEAP_PROPERTIES GetHeapProp(); // ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc(); // リソースディスクリプタ


public:
    HRESULT CreateConstObj(ID3D12Device* device); // コンスタントオブジェクト作成
    ID3D12Resource* GetBuff(); // バッファを返す

    void RotationY(float pi);

    Const();
    ~Const();
};