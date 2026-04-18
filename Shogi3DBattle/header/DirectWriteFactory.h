#pragma once

#include<dwrite.h>
#include<wrl.h>
#include<string>

class DirectWriteFactory
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDWriteFactory> _dWriteFactory;

    ComPtr<IDWriteTextFormat> CreateTextFormat( // テキストフォーマット作成
        DWRITE_FONT_WEIGHT weight,
        float              fontSize);

    ComPtr<IDWriteTextFormat> CreateHTextFormat( // 横書きテキストフォーマット作成
        DWRITE_FONT_WEIGHT weight,
        float              fontSize);

    ComPtr<IDWriteTextFormat> CreateVTextFormat( // 縦書きテキストフォーマット作成
        DWRITE_FONT_WEIGHT weight,
        float              fontSize);
public:
    ComPtr<IDWriteTextFormat> CreatePieceTextFormat(); // 駒用テキストフォーマット作成
    ComPtr<IDWriteTextFormat> CreateUITextFormat();    // UI用テキストフォーマット作成
    ComPtr<IDWriteTextFormat> CreateTitleTextFormat(DWRITE_FONT_WEIGHT weight); // タイトルテキストフォーマット作成

    DirectWriteFactory();
};