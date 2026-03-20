#pragma once

#include<d3d12.h>
#include<wrl.h>

class Heap
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
    ComPtr<ID3D12DescriptorHeap> _heap; // ヒープ
    UINT _descOffset; // ディスクリプタオフセット

public:
    enum HeapType // ヒープタイプ ヒープ作成時に使用
    {
        RTV, // レンダーターゲットビュー
        DSV, // デプスステンシルビュー
        CSU  // コンスタントバッファビュー、シェーダーリソースビュー、アンオーダーアクセスビュー
    };

    D3D12_CPU_DESCRIPTOR_HANDLE GetDescHandle(UINT i);    // 引数の位置のディスクリプタハンドルを返す
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescHandle(UINT i); // 引数の位置のGPUディスクリプタハンドルを返す
    UINT GetDescNum(); // ディスクリプタの数を返す

    void SetHeap(ComPtr<ID3D12DescriptorHeap> heap); // ヒープセット
    ID3D12DescriptorHeap* GetHeap(); // ヒープを返す
    void SetDescOffset(UINT RTVOffset); // ディスクリプタオフセットセット

    Heap();
    ~Heap();
};