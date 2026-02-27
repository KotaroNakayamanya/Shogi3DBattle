#include"DX12.h"
#include"Draw.h"

#include<algorithm>
#include<string>
#include<cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace {
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    void EnableDebugLayer()
    {
        ComPtr<ID3D12Debug> debugLayer = nullptr;

        D3D12GetDebugInterface(
            IID_PPV_ARGS(debugLayer.ReleaseAndGetAddressOf()));

        debugLayer->EnableDebugLayer();
    }
}


// DirectX12初期設定
bool DX12::CreateDX12Object()
{
    // DXGIファクトリー作成
    if (FAILED(CreateFactory()))
    {
        assert(false); return false;
    }

    // 使用するアダプターを決定
    CreateUsedAdapterLists();
    DecisionUsingAdapter();

    // デバイス作成（GPU機能レベルに対応していなければ失敗）
    if (FAILED(CreateDevice()))
    {
        assert(false); return false;
    }  

    // 描画オブジェクト作成
    if (FAILED(CreateDrawObject()))
    {
        assert(false); return false;
    }

    // レンダーターゲットビュー作成
    if (FAILED(CreateRTVHeap()))
    {
        assert(false); return false;
    }
    if (FAILED(CreateRTV()))
    {
        assert(false); return false;
    }

    return true;
}

HRESULT DX12::CreateFactory()
{
    HRESULT result;
    // デバッグモードのときは詳細を表示させるものを使用する
#ifdef _DEBUG
    result = CreateDXGIFactory2(
        DXGI_CREATE_FACTORY_DEBUG,
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#else
    result = CreateDXGIFactory1(
        IID_PPV_ARGS(_dxgiFactory.ReleaseAndGetAddressOf()));
#endif

    return result;
}

// 使われているアダプタ（GPU）を動的配列に入れる
void DX12::CreateUsedAdapterLists()
{
    ComPtr<IDXGIAdapter> tmpAdapter;
    int i = 0;
    while (_dxgiFactory->EnumAdapters(i, tmpAdapter.ReleaseAndGetAddressOf())
           != DXGI_ERROR_NOT_FOUND)
    {
        _adapters.push_back(tmpAdapter.Get());
        i++;
    }
}

// 使用するアダプターを決定
void DX12::DecisionUsingAdapter()
{
    for(auto adapter : _adapters)
    {
        // アダプター説明オブジェクト取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);

        std::wstring str = adapterDesc.Description;

        if (str.find(L"NVIDIA") != std::string::npos)
        {
            _usingAdapter.Swap(adapter);
            break;
        }
    }
}

// デバイス作成
HRESULT DX12::CreateDevice()
{
    HRESULT result;
    // GPU機能レベルの配列順にデバイス作成を試みる
    std::find_if(_featureLevels.begin(), _featureLevels.end(),
        [this, &result](D3D_FEATURE_LEVEL featureLevel)
        {
            result = D3D12CreateDevice(
                _usingAdapter.Get(),
                featureLevel,
                IID_PPV_ARGS(_device.ReleaseAndGetAddressOf()));

            return result == S_OK; // 作成できたら戻る
        });

    return result;
}

// 描画オブジェクト（コマンド、スワップチェーン、フェンス）を作成
HRESULT DX12::CreateDrawObject()
{
    return _draw->CreateDrawObject(
        _device.Get(),
        _dxgiFactory.Get(),
        _hwnd);
}

// レンダーターゲットビューヒープ作成
HRESULT DX12::CreateRTVHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = GetRTVHeapDesc();

    return _device->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(_rtvHeap.ReleaseAndGetAddressOf()));
}

// RTVヒープディスクリプタを返す
D3D12_DESCRIPTOR_HEAP_DESC DX12::GetRTVHeapDesc()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.Type =
        D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask =
        0;
    desc.NumDescriptors =
        _bufferNum;
    desc.Flags =
        D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    return desc;
}

// レンダーターゲットビュー作成
HRESULT DX12::CreateRTV()
{
    // ヒープの先頭アドレスを取得しておく
    D3D12_CPU_DESCRIPTOR_HANDLE destinationPtr =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();

    _rtvs.resize(_bufferNum);

    for (int i = 0; i < _bufferNum; i++)
    {
        if (FAILED(SetBufferToRTV(i)))
        {
            assert(false); return E_FAIL;
        }

        _device->CreateRenderTargetView(
            _rtvs[i].Get(),
            nullptr,
            destinationPtr);

        // RTVビューを入れた分、アドレスを足す
        destinationPtr.ptr +=
            _device->GetDescriptorHandleIncrementSize(
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    return S_OK;
}

// 各RTVにバッファを対応させる
HRESULT DX12::SetBufferToRTV(UINT i)
{
    return _draw->SetBufferToRTV(
        i, _rtvs[i].ReleaseAndGetAddressOf());
}




// コマンド実行
void DX12::ExecuteDX12()
{
    // 現在のバックバッファのインデックス、ハンドルを取得
    auto backBufferIdx = GetBackBufferIdx();
    auto rtvHandle = GetRTVHandle(backBufferIdx);

    // バックバッファに対応するRTVをレンダーターゲットに設定
    ChangeRTVToRenderTarget(_rtvs[backBufferIdx].Get());
    SetRenderTarget(rtvHandle);

    // レンダーターゲットクリア
    ClearRenderTarget(rtvHandle);

    // バックバッファに対応するRTVを表示画面に設定
    ChangeRTVToPresent(_rtvs[backBufferIdx].Get());

    // コマンド実行および同期処理
    CloseCommand();
    ExecuteCommand();
    WaitProcessWithFence();
    ResetCommand();
    
    // 画面スワップ
    DisplaySwap();

    return;
}


UINT DX12::GetBackBufferIdx(){return _draw->GetBackBufferIdx();}

D3D12_CPU_DESCRIPTOR_HANDLE DX12::GetRTVHandle(UINT idx)
{
    auto handle =
        _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    auto offset =
        _device->GetDescriptorHandleIncrementSize(
              D3D12_DESCRIPTOR_HEAP_TYPE_RTV); 
    handle.ptr += idx * offset;

    return handle;
}


void DX12::ChangeRTVToRenderTarget(ID3D12Resource* rtv){_draw->ChangeRTVToRenderTarget(rtv);}
void DX12::ChangeRTVToPresent     (ID3D12Resource* rtv){_draw->ChangeRTVToPresent     (rtv);}

void DX12::SetRenderTarget  (D3D12_CPU_DESCRIPTOR_HANDLE handle){_draw->SetRenderTarget  (handle);}
void DX12::ClearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE handle){_draw->ClearRenderTarget(handle);}

void DX12::CloseCommand()  {_draw->CloseCommand();  }
void DX12::ExecuteCommand(){_draw->ExecuteCommand();}
void DX12::ResetCommand()  {_draw->ResetCommand();  }

void DX12::WaitProcessWithFence(){_draw->WaitProcessWithFence();}
void DX12::DisplaySwap(){_draw->DisplaySwap();}




DX12::DX12(HWND hwnd)
{
#ifdef _DEBUG
    ::EnableDebugLayer();
#endif

    _hwnd = hwnd;
    _draw.reset(new Draw(_bufferNum));
}