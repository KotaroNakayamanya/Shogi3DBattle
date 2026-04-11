#pragma once

#include<string>
#include<dwrite.h>
#include<d2d1_3.h>

struct Text2D
{
    std::wstring          text;       // テキスト
    IDWriteTextFormat*    textFormat; // テキストフォーマット
    ID2D1SolidColorBrush* brush;      // ブラシ
    D2D1_RECT_F           rect;       // 範囲
};