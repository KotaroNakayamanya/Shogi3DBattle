#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<memory>
#include<vector>

#include"DrawArg.h"

class CommandAllocator;
class CommandList;
class CommandQueue;
class SwapChain;
class Fence;

class Draw
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    UINT _buffNum;  // バッファー数（スワップチェーン作成に利用）
    //UINT _fenceVal = 0; // フェンスの同期処理確認用

    std::unique_ptr<CommandAllocator> _commandAllocator;     // コマンドアロケータオブジェクト
    HRESULT CreateCommandAllocatorObj(ID3D12Device* device); // コマンドアロケータオブジェクト作成

    std::unique_ptr<CommandList> _commandList;          // コマンドアロケータオブジェクト
    HRESULT CreateCommandListObj(ID3D12Device* device); // コマンドアロケータオブジェクト作成

    std::unique_ptr<CommandQueue> _commandQueue;         // コマンドキューオブジェクト
    HRESULT CreateCommandQueueObj(ID3D12Device* device); // コマンドキューオブジェクト作成

    std::unique_ptr<SwapChain> _swapChain; // スワップチェーンオブジェクト
    HRESULT CreateSwapChainObj(            // スワップチェーンオブジェクト作成
        IDXGIFactory6* dxgiFactory,
        HWND hwnd);

    std::unique_ptr<Fence> _fence;         // コマンドキューオブジェクト
    HRESULT CreateFenceObj(ID3D12Device* device); // コマンドキューオブジェクト作成

    //ComPtr<ID3D12Fence>                 _fence;            // フェンス
    ComPtr<ID3D12DescriptorHeap>        _rtvHeap;          // RTVヒープ
    std::vector<ComPtr<ID3D12Resource>> _rtvs;             // RTV

    //HRESULT CreateFence(ID3D12Device* device); // フェンス作成
    HRESULT CreateRTVHeap(ID3D12Device* device); // RTVヒープ作成
    HRESULT CreateRTV(ID3D12Device* device); // RTV作成

    
    HRESULT SetRTVBuffer(UINT i); // RTVにバッファを対応させる

    void ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier);
    void ChangeRTVBarrierToPresent     (D3D12_RESOURCE_BARRIER resourceBarrier);

    void ExeCommand(); // コマンド実行
    void ResetCommand  (); // コマンドリセット

    void WaitProcessWithFence(); // フェンスによる同期処理

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // RTVヒープディスクリプタ


public:
    // 描画オブジェクト生成
    HRESULT CreateDrawObj(DrawArg::CreateDrawObjArg arg);
    // レンダーターゲットの準備
    void PrepareRenderTarget(DrawArg::PrepareRenderTargetArg arg);
    // コマンドセット
    void SetCommand(DrawArg::SetCommandArg arg);
    // 描画実行
    void ExeDraw(DrawArg::ExeDrawArg arg);

    Draw(UINT bufferNum);
    ~Draw();
};