#include"TextFormatFactory.h"
#include"Application.h"

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 駒用フォーマット作成
ComPtr<IDWriteTextFormat> TextFormatFactory::CreatePieceTextFormat(std::wstring fontName)
{
    ComPtr<IDWriteTextFormat> comPtr;

    _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        50.0f,
        L"ja-jp",
        comPtr.ReleaseAndGetAddressOf());

    // 横位置を中央に
    comPtr->SetTextAlignment(
        DWRITE_TEXT_ALIGNMENT_CENTER);

    // 縦位置を中央に
    comPtr->SetParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    // 縦書きにする
    comPtr->SetReadingDirection(
        DWRITE_READING_DIRECTION_TOP_TO_BOTTOM);

    // 右から左へ
    comPtr->SetFlowDirection(
        DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT);

    return comPtr;
}

// UIテキストフォーマット作成
ComPtr<IDWriteTextFormat> TextFormatFactory::CreateUITextFormat(std::wstring fontName)
{
    ComPtr<IDWriteTextFormat> ComPtr;

    auto gameWindow = Application::GetInstance().GetGameWindow();
    auto fontSize   = gameWindow->GetWindowHeight() / 20;

    _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        fontSize,
        L"ja-jp",
        ComPtr.ReleaseAndGetAddressOf());

    // 横位置を中央に
    ComPtr->SetTextAlignment(
        DWRITE_TEXT_ALIGNMENT_CENTER);

    // 縦位置を中央に
    ComPtr->SetParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return ComPtr;
}

TextFormatFactory::TextFormatFactory()
{
    ComPtr<IDWriteFactory> comPtr;

    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(comPtr.ReleaseAndGetAddressOf()));

    _dWriteFactory = comPtr;
}