#pragma once

#include<dwrite.h>
#include<wrl.h>
#include"TextFormat.h"
#include<string>

class DWriteFactory
{
    friend class DX12; // DX12クラスから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDWriteFactory> _dWriteFactory;

public:
    // テキストフォーマット作成
    HRESULT CreateTextFormat(
        TextFormat* textFormat,
        std::wstring fontName);

    DWriteFactory();
    ~DWriteFactory();
};