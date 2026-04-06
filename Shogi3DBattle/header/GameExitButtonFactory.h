#pragma once

#include"IButtonUIFactory.h"

class GameExitButtonFactory : public IButtonUIFactory
{
public:
    std::unique_ptr<IButtonUI> CreateButtonUI( // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“ì¬
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};
