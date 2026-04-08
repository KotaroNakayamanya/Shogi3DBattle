#pragma once

#include"I_ButtonUIFactory.h"

class ContinueStartButtonFactory : public I_ButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // ‚Â‚Â‚«‚©‚çƒ{ƒ^ƒ“ì¬
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};
