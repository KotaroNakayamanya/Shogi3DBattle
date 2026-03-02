#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>

class Draw
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    UINT _bufferCount;  // バッファー数（スワップチェーン作成に利用）
    UINT _fenceVal = 0; // フェンスの同期処理確認用
    
    ComPtr<ID3D12CommandAllocator>      _commandAllocator; // コマンドアロケータ
    ComPtr<ID3D12GraphicsCommandList>   _commandList;      // コマンドリスト
    ComPtr<ID3D12CommandQueue>          _commandQueue;     // コマンドキュー
    ComPtr<IDXGISwapChain4>             _swapChain;        // スワップチェーン
    ComPtr<ID3D12Fence>                 _fence;            // フェンス
    //ComPtr<ID3D12DescriptorHeap>        _rtvHeap;          // RTVヒープ


    HRESULT CreateCommandAllocator(ID3D12Device* device); // コマンドアロケータ作成
    HRESULT CreateCommandList(ID3D12Device* device);      // コマンドリスト作成
    HRESULT CreateCommandQueue(                           // コマンドキュー作成
        ID3D12Device*            device,
        D3D12_COMMAND_QUEUE_DESC commandQueueDesc);
    HRESULT CreateSwapChain(                              // スワップチェーン作成
        IDXGIFactory6*        dxgiFactory,
        HWND                  hwnd,
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc);
    HRESULT CreateFence(ID3D12Device* device);            // フェンス作成
    //HRESULT CreateRTVHeap(); // RTVヒープ作成


    D3D12_RESOURCE_BARRIER GetBufferBarrierDesc(ID3D12Resource* rtv);

    // RTVのレンダーターゲット⇔Presentの切り替え
    void ChangeRTVBarrierToRenderTarget(ID3D12Resource* rtv);
    void ChangeRTVBarrierToPresent     (ID3D12Resource* rtv);

    void SetRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);

    void ExecuteCommand(); // コマンド実行
    void ResetCommand  (); // コマンドリセット

    void WaitProcessWithFence(); // フェンスによる同期処理

    void ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle);


public:
    Draw(UINT bufferNum);

    // 描画オブジェクト生成
    HRESULT CreateDrawObject(
        ID3D12Device*            device,
        IDXGIFactory6*           dxgiFactory,
        HWND                     hwnd,
        D3D12_COMMAND_QUEUE_DESC commandQueueDesc,
        DXGI_SWAP_CHAIN_DESC1    swapChainDesc);

    HRESULT SetBufferToRTV(UINT i, ID3D12Resource** rtvPtr);

    // レンダーターゲットの準備
    void PrepareRenderTarget(
        D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle,
        UINT rtvOffset,
        std::vector<ComPtr<ID3D12Resource>> rtvs);

    // 描画実行
    void ExecuteDraw(std::vector<ComPtr<ID3D12Resource>> rtvs);




    
   


    

    





    // パイプラインセット
    void SetPipeLineState(ID3D12PipelineState* pipelineState);
    // ルートシグネチャセット
    void SetRootSignature(ID3D12RootSignature* rootSignature);
    // ビューポートセット
    void SetViewports(D3D12_VIEWPORT viewport);
    // シザー矩形セット
    void SetScissorRects(D3D12_RECT scissorRect);
    // プリミティブトポロジーセット
    void SetPremitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);
    // 頂点バッファのセット
    void SetVertexBuffers(D3D12_VERTEX_BUFFER_VIEW vertexBufferView); 
    // インデックスバッファのセット
    void SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW indexBufferView); 
    // 描画命令セット
    void SetDrawInstanced(UINT vertexCount, UINT objectCount);

    
};