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
    return _dWriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        100.0f,
        L"ja-jp",
        dWriteTextFormat->_dWriteTextFormat.ReleaseAndGetAddressOf());
}



DWriteFactory::DWriteFactory(){}
DWriteFactory::~DWriteFactory(){}