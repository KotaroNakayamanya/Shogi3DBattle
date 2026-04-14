#pragma once

#include<dwrite.h>
#include<wrl.h>
#include<string>

class TextFormatFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDWriteFactory> _dWriteFactory;

public:
    // テキストフォーマット作成
    ComPtr<IDWriteTextFormat> CreatePieceTextFormat(std::wstring fontName);

    ComPtr<IDWriteTextFormat> CreateUITextFormat(std::wstring fontName);

    TextFormatFactory();
};