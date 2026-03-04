#pragma once

#include<d3d12.h>
#include<wrl.h>

class Const
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _buff; // コンスタントバッファ
    ComPtr<ID3D12DescriptorHeap> _heap; // ディスクリプタヒープ

    HRESULT CreateBuff(ID3D12Device* device); // コンスタントバッファ作成
    HRESULT CreateHeap(ID3D12Device* device); // ディスクリプタヒープ作成
    void CreateCBV(ID3D12Device* device); // CBV作成


    D3D12_HEAP_PROPERTIES GetHeapProp(); // ヒーププロパティ
    D3D12_RESOURCE_DESC GetResourceDesc(); // リソースディスクリプタ
    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // ヒープディスクリプタ
    D3D12_CONSTANT_BUFFER_VIEW_DESC GetCBVDesc(); // CBVディスクリプタ

public:
    HRESULT CreateConstObj(ID3D12Device* device); // コンスタントオブジェクト作成
    HRESULT MapBuff();


    Const();
    ~Const();
};