#include"Adapter.h"

#include<string>
#include<array>

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 使用するアダプター作成
HRESULT Adapter::CreateAdapter(IDXGIFactory6* dxgiFactory)
{
    // 探索対象のアダプター名
    std::array<std::wstring, 3> adapterNames =
    {
        L"NVIDIA",
        L"AMD",
        L"Intel"
    };

    // 使用可能なアダプターを取得
    std::vector<ComPtr<IDXGIAdapter>> canUseAdapters =
        GetCanUseAdapters(dxgiFactory);
    // 使用可能なアダプターがなければ失敗を返す
    if(canUseAdapters.size() == 0) return E_FAIL;
    

    for(auto& adapter : canUseAdapters)
    {
        // アダプター名取得
        DXGI_ADAPTER_DESC adapterDesc;
        adapter->GetDesc(&adapterDesc);
        std::wstring descStr = adapterDesc.Description;

        // リストに存在するアダプターであれば利用する
        auto it = std::find(adapterNames.begin(), adapterNames.begin(), descStr);
        if (it != adapterNames.end())
        {
            _adapter = adapter;
            goto complete;
        }
    }

    // 見つからなければ一番最初のアダプターを利用する
    _adapter = canUseAdapters[0];

complete:
    return S_OK;
}

// 使用可能なアダプターを取得
std::vector<ComPtr<IDXGIAdapter>> Adapter::GetCanUseAdapters(IDXGIFactory6* dxgiFactory)
{
    std::vector<ComPtr<IDXGIAdapter>> adapters;
    ComPtr<IDXGIAdapter> tmpAdapter;
    
    int i = 0;
    while (dxgiFactory->EnumAdapters(i, tmpAdapter.ReleaseAndGetAddressOf())
           != DXGI_ERROR_NOT_FOUND)
    {
        adapters.push_back(tmpAdapter);
        i++;
    }

    return adapters;
}




// 使用するアダプターを渡す
IDXGIAdapter* Adapter::GetAdapter()
{
    return _adapter.Get();
}





Adapter::Adapter(){}
Adapter::~Adapter(){}