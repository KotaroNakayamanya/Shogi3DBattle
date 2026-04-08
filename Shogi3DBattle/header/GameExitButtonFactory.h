#pragma once

#include"I_ButtonUIFactory.h"

class GameExitButtonFactory : public I_ButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“ì¬
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};
