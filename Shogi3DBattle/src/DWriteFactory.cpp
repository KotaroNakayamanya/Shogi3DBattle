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
//        dWriteTextFormat->_dWriteTextFormat.ReleaseAndGetAddressOf());
//}

// テキストフォーマット作成
HRESULT DWriteFactory::CreateDWriteTextFormat(
    DWriteTextFormat* dWriteTextFormat,
    std::wstring fontName)
{
    HRESULT result;

    result = _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
        60.0f,
        L"ja-jp",
        dWriteTextFormat->_dWriteTextFormat.ReleaseAndGetAddressOf());
    if(FAILED(result)) return result;

    // 横位置を中央に
    result = dWriteTextFormat->_dWriteTextFormat->SetTextAlignment(
        DWRITE_TEXT_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    // 縦位置を中央に
    result = dWriteTextFormat->_dWriteTextFormat->SetParagraphAlignment(
        DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if(FAILED(result)) return result;

    // 縦書きにする
    result = dWriteTextFormat->_dWriteTextFormat->SetReadingDirection(
        DWRITE_READING_DIRECTION_TOP_TO_BOTTOM);
    if(FAILED(result)) return result;

    // 右から左へ
    result = dWriteTextFormat->_dWriteTextFormat->SetFlowDirection(
        DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT);
    if(FAILED(result)) return result;

    result = S_OK;
}



DWriteFactory::DWriteFactory(){}
DWriteFactory::~DWriteFactory(){}