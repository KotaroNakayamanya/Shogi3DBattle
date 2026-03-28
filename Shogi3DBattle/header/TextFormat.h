#pragma once

#include<dwrite.h>
#include<wrl.h>

class TextFormat
{
    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDWriteTextFormat> _textFormat; // テキストフォーマット

public:
    void SetTextFormat(ComPtr<IDWriteTextFormat> textFormat); // テキストフォーマットセット
    IDWriteTextFormat* GetTextFormat();                       // テキストフォーマットを返す

    TextFormat();
    ~TextFormat();
};