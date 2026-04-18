#include"DirectWriteFactory.h"
#include"Application.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// テキストフォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreateTextFormat(
    DWRITE_FONT_WEIGHT weight,
    float              fontSize)
{
    ComPtr<IDWriteTextFormat> comPtr;

    HRESULT result;
    result = _dWriteFactory->CreateTextFormat(
        L"メイリオ",
        nullptr,
        weight,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        fontSize,
        L"ja-jp",
        comPtr.ReleaseAndGetAddressOf());
    assert(SUCCEEDED(result));

    return comPtr;
}

// 横書きテキストフォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreateHTextFormat(
    DWRITE_FONT_WEIGHT weight,
    float              fontSize)
{
    auto comPtr = CreateTextFormat(weight, fontSize);

    HRESULT result;
    result = comPtr->SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT); assert(SUCCEEDED(result)); // 横書き
    result = comPtr->SetFlowDirection   (DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM);    assert(SUCCEEDED(result)); // 上から下へ
    
    return comPtr;
}

// 縦書きテキストフォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreateVTextFormat(
    DWRITE_FONT_WEIGHT weight,
    float              fontSize)
{
    auto comPtr = CreateTextFormat(weight, fontSize);

    HRESULT result;
    result = comPtr->SetReadingDirection(DWRITE_READING_DIRECTION_TOP_TO_BOTTOM); assert(SUCCEEDED(result)); // 縦書き
    result = comPtr->SetFlowDirection   (DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT);    assert(SUCCEEDED(result)); // 右から左へ
    
    return comPtr;
}




// 駒用フォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreatePieceTextFormat()
{
    auto weight   = DWRITE_FONT_WEIGHT_BOLD;
    auto fontSize = 50.0f;

    auto comPtr = CreateVTextFormat(weight, fontSize);

    HRESULT result; 
    result = comPtr->SetTextAlignment     (DWRITE_TEXT_ALIGNMENT_CENTER);      assert(SUCCEEDED(result)); // 横位置を中央に
    result = comPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); assert(SUCCEEDED(result)); // 縦位置を中央に

    return comPtr;
}

// UIテキストフォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreateUITextFormat()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();

    auto weight   = DWRITE_FONT_WEIGHT_BOLD;
    auto fontSize = gameWindow->GetWindowHeight() / 20.0f;

    auto comPtr = CreateHTextFormat(weight, fontSize);
    
    comPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);           // 横位置を中央に
    comPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // 縦位置を中央に

    return comPtr;
}
// タイトルテキストフォーマット作成
ComPtr<IDWriteTextFormat> DirectWriteFactory::CreateTitleTextFormat(DWRITE_FONT_WEIGHT weight)
{
    auto fontSize = 120.0f;

    auto comPtr = CreateHTextFormat(weight, fontSize);

    comPtr->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);           // 横位置を中央に
    comPtr->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // 縦位置を中央に

    return comPtr;
}




DirectWriteFactory::DirectWriteFactory()
{
    ComPtr<IDWriteFactory> comPtr;

    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(comPtr.ReleaseAndGetAddressOf()));

    _dWriteFactory = comPtr;
}