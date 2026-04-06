#pragma once

#include"IButtonUIFactory.h"

class NewStartButtonFactory : public IButtonUIFactory
{
public:
    std::unique_ptr<IButtonUI> CreateButtonUI( // ‚Í‚¶‚ß‚©‚çƒ{ƒ^ƒ“UIì¬
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};