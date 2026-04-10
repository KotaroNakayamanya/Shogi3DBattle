#pragma once

#include"d2d1_3.h"

class UI
{
private:
    D2D1_RECT_F _rect;         // UI”ÍˆÍ

public:
    void        SetRect(D2D1_RECT_F rect); // UI”ÍˆÍƒZƒbƒg
    D2D1_RECT_F GetRect();                 // UI”ÍˆÍ‚ð•Ô‚·

    UI(D2D1_RECT_F rect);
};