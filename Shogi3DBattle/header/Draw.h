#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<memory>

#include"CommandAllocator.h"
#include"CommandList.h"
#include"CommandQueue.h"
#include"SwapChain.h"
#include"RTVHeap.h"
#include"DSBuff.h"
#include"DSVHeap.h"
#include"Fence.h"


#include"DrawArg.h"
#include"DXGIFactoryArg.h"

class Draw
{
private:
    UINT _buffNum;  // バッファー数（スワップチェーン作成に利用）
    UINT _rtvOffset; // RTVバイト数

    std::unique_ptr<CommandAllocator> _commandAllocator;     // コマンドアロケータオブジェクト
    HRESULT CreateCommandAllocatorObj(ID3D12Device* device); // コマンドアロケータオブジェクト作成

    std::unique_ptr<CommandList> _commandList;          // コマンドアロケータオブジェクト
    HRESULT CreateCommandListObj(ID3D12Device* device); // コマンドアロケータオブジェクト作成

    std::unique_ptr<CommandQueue> _commandQueue;         // コマンドキューオブジェクト
    HRESULT CreateCommandQueueObj(ID3D12Device* device); // コマンドキューオブジェクト作成

    std::unique_ptr<SwapChain> _swapChain; // スワップチェーンオブジェクト
    HRESULT CreateSwapChainObj(            // スワップチェーンオブジェクト作成
        DXGIFactory* dxgiFactoryObj,
        HWND hwnd,
        UINT windowWidth,
        UINT windowHeight);
    DXGIFactoryArg::CreateSwapChainArg GetCreateSwapChainArg( // スワップチェーン作成用引数
        ID3D12CommandQueue* commandQueue,
        HWND hwnd,
        UINT windowWidth,
        UINT windowHeight);

    std::unique_ptr<DSBuff> _dsBuff; // デプスステンシルバッファ
    HRESULT CreateDSBuffObj(         // デプスステンシルバッファ作成
    ID3D12Device* device,
    UINT windowWidth,
    UINT windowHeight);
    std::unique_ptr<DSVHeap> _dsvHeap;              // デプスステンシルヒープ
    HRESULT CreateDSVHeapObj(ID3D12Device* device); // デプスステンシルヒープ作成

    std::unique_ptr<RTVHeap> _rtvHeap;              // RTVヒープオブジェクト
    HRESULT CreateRTVHeapObj(ID3D12Device* device); // RTVヒープオブジェクト作成 
    HRESULT CreateRTV( // RTV作成
        ID3D12Device* device,
        IDXGISwapChain4* swapChain,
        UINT buffNum);
    

    std::unique_ptr<Fence> _fence;                // フェンスオブジェクト
    HRESULT CreateFenceObj(ID3D12Device* device); // フェンスオブジェクト作成




    D3D12_VIEWPORT _viewport; // ビューポート
    void CreateViewports(     // ビューポート作成
        UINT windowWidth, UINT windowHeight);

    D3D12_RECT _scissorRect; // シザー矩形
    void CreateScissorRects( // シザー矩形作成
        UINT windowWidth, UINT windowHeight);

    D3D12_RESOURCE_BARRIER _basicResourceBarrier; // 基本リソースバリア
    void CreateBasiceResourceBarrier();           // 基本リソースバリア作成


    void ChangeRTVBarrierToRenderTarget(UINT backBufferIdx);
    void ChangeRTVBarrierToPresent     (UINT backBufferIdx);

    void ExeCommand(); // コマンド実行
    void ResetCommand  (); // コマンドリセット

    void WaitProcessWithFence(); // フェンスによる同期処理

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    D3D12_DESCRIPTOR_HEAP_DESC GetHeapDesc(); // RTVヒープディスクリプタ


public:
    HRESULT CreateDrawObj(DrawArg::CreateDrawObjArg arg); // 描画オブジェクト生成

    void PrepareRenderTarget(); // レンダーターゲットの準備

    void SetCommand(DrawArg::SetCommandArg arg); // コマンドセット

    void ExeDraw(); // 描画実行

    HRESULT UpdateDrawConf( //描画設定更新
        ID3D12Device* device,
        UINT width, 
        UINT height,
        UINT buffNum);

    Draw(UINT buffNum);
    Draw();
    ~Draw();
};