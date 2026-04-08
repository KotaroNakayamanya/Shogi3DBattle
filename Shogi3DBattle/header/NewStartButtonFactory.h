#pragma once

#include"IButtonUIFactory.h"

class NewStartButtonFactory : public IButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // ÇÕÇ∂ÇﬂÇ©ÇÁÉ{É^ÉìçÏê¨
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};