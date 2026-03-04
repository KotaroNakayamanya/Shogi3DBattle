#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>

#include"DrawArg.h"

class Draw
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    UINT _buffNum;  // バッファー数（スワップチェーン作成に利用）
    UINT _fenceVal = 0; // フェンスの同期処理確認用
    

    ComPtr<ID3D12CommandAllocator>      _commandAllocator; // コマンドアロケータ
    ComPtr<ID3D12GraphicsCommandList>   _commandList;      // コマンドリスト
    ComPtr<ID3D12CommandQueue>          _commandQueue;     // コマンドキュー
    ComPtr<IDXGISwapChain4>             _swapChain;        // スワップチェーン
    ComPtr<ID3D12Fence>                 _fence;            // フェンス
    ComPtr<ID3D12DescriptorHeap>        _rtvHeap;          // RTVヒープ
    std::vector<ComPtr<ID3D12Resource>> _rtvs;             // RTV

    HRESULT CreateCommandAllocator( // コマンドアロケータ作成
        ID3D12Device* device);
    HRESULT CreateCommandList(      // コマンドリスト作成
        ID3D12Device* device);    
    HRESULT CreateCommandQueue(     // コマンドキュー作成
        ID3D12Device*            device,
        D3D12_COMMAND_QUEUE_DESC commandQueueDesc);
    HRESULT CreateSwapChain(        // スワップチェーン作成
        IDXGIFactory6*        dxgiFactory,
        HWND                  hwnd,
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc);
    HRESULT CreateFence(            // フェンス作成
        ID3D12Device* device);       
    HRESULT CreateRTVHeap(          // RTVヒープ作成
        ID3D12Device*              device,
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc); 
    HRESULT CreateRTV(              // RTV作成
        ID3D12Device* device);

    // RTVにバッファを対応させる
    HRESULT SetRTVBuffer(UINT i);

    void ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier);
    void ChangeRTVBarrierToPresent     (D3D12_RESOURCE_BARRIER resourceBarrier);

    void ExeCommand(); // コマンド実行
    void ResetCommand  (); // コマンドリセット

    void WaitProcessWithFence(); // フェンスによる同期処理

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);


public:
    Draw(UINT bufferNum);
    ~Draw();

    // 描画オブジェクト生成
    HRESULT CreateDrawObj(DrawArg::CreateDrawObjArg arg);
    // レンダーターゲットの準備
    void PrepareRenderTarget(DrawArg::PrepareRenderTargetArg arg);
    // コマンドセット
    void SetCommand(DrawArg::SetCommandArg arg);
    // 描画実行
    void ExeDraw(DrawArg::ExeDrawArg arg);
};