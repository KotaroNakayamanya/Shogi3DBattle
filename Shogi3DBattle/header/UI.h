#pragma once

#include"d2d1_3.h"

class UI
{
protected:
    D2D1_RECT_F _rect;     // UI”ÍˆÍ
    bool        _isActive; // Šˆ«‚©‚Ç‚¤‚©

public:
    D2D1_RECT_F GetRect(); // UI”ÍˆÍ‚ğ•Ô‚·

    void   SetIsActive(bool active); // Šˆ«ó‘ÔƒZƒbƒg
    bool   GetIsActive();            // Šˆ«ó‘Ô‚ğ•Ô‚·

    UI(D2D1_RECT_F rect, bool active = true);
};