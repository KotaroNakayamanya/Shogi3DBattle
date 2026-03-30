#include"DWriteFactory.h"

//// テキストフォーマット作成
//HRESULT DWriteFactory::CreateDWriteTextFormat(
//    DWriteTextFormat* dWriteTextFormat)
//{
//    return _dWriteFactory->CreateTextFormat(
//        L"メイリオ",
//        nullptr,
//        DWRITE_FONT_WEIGHT_NORMAL,
//        DWRITE_FONT_STYLE_NORMAL,
//        DWRITE_FONT_STRETCH_NORMAL,
//        100.0f,
//        L"ja-jp",
//        textFormatCom.ReleaseAndGetAddressOf());
//}

// テキストフォーマット作成
HRESULT DWriteFactory::CreateTextFormat(
    TextFormat* textFormat,
    std::wstring fontName)
{
    ComPtr<IDWriteTextFormat> textFormatCom;

    HRESULT result;

    result = _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        50.0f,
        L"ja-jp",
        textFormatCom.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    // 横位置を中央に
    result = textFormatCom->SetTextAlignment(
        DWRITE_TEXT_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    // 縦位置を中央に
    result = textFormatCom->SetParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    // 縦書きにする
    result = textFormatCom->SetReadingDirection(
        DWRITE_READING_DIRECTION_TOP_TO_BOTTOM);
    if(FAILED(result)) return result;

    // 右から左へ
    result = textFormatCom->SetFlowDirection(
        DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT);
    if(FAILED(result)) return result;

    textFormat->SetTextFormat(textFormatCom);
    result = S_OK;
}

// UIテキストフォーマット作成
HRESULT DWriteFactory::CreateUITextFormat(
    TextFormat* textFormat,
    std::wstring fontName,
    float fontSize)
{
    ComPtr<IDWriteTextFormat> textFormatCom;

    HRESULT result;

    result = _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        fontSize,
        L"ja-jp",
        textFormatCom.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    // 横位置を中央に
    result = textFormatCom->SetTextAlignment(
        DWRITE_TEXT_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    // 縦位置を中央に
    result = textFormatCom->SetParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    textFormat->SetTextFormat(textFormatCom);
    result = S_OK;
}



DWriteFactory::DWriteFactory(){}
DWriteFactory::~DWriteFactory(){}