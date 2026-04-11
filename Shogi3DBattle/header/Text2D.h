#pragma once

#include<string>
#include<d2d1_3.h>

struct Text2D
{
    std::wstring text; // テキスト
    D2D1_RECT_F  rect; // テキスト表示範囲
};