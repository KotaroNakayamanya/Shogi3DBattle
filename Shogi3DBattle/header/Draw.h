#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<memory>

#include"CommandAllocator.h"
#include"CommandList.h"
#include"CommandQueue.h"
#include"SwapChain.h"
#include"Fence.h"
#include"RTVHeap.h"

#include"DrawArg.h"

class Draw
{
private:
    UINT _buffNum;  // バッファー数（スワップチェーン作成に利用）

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

    std::shared_ptr<RTVHeap> _heap;                 // ヒープオブジェクト
    HRESULT CreateHeapObj(ID3D12Device* device); // ヒープオブジェクト作成 


    void ChangeRTVBarrierToRenderTarget(D3D12_RESOURCE_BARRIER resourceBarrier);
    void ChangeRTVBarrierToPresent     (D3D12_RESOURCE_BARRIER resourceBarrier);

    void ExeCommand(); // コマンド実行
    void ResetCommand  (); // コマンドリセット

    void WaitProcessWithFence(); // フェンスによる同期処理

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // RTVヒープディスクリプタ


public:
    HRESULT CreateDrawObj(DrawArg::CreateDrawObjArg arg); // 描画オブジェクト生成
    void PrepareRenderTarget(DrawArg::PrepareRenderTargetArg arg); // レンダーターゲットの準備
    void SetCommand(DrawArg::SetCommandArg arg); // コマンドセット
    void ExeDraw(DrawArg::ExeDrawArg arg); // 描画実行

    Draw(UINT bufferNum);
    Draw();
    ~Draw();
};