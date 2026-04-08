#pragma once

#include"I_ButtonUIFactory.h"

class NewStartButtonFactory : public I_ButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // ÇÕÇ∂ÇﬂÇ©ÇÁÉ{É^ÉìçÏê¨
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};