#pragma once

#include"IButtonUIFactory.h"

class OptionButtonFactory : public IButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // オプションボタン作成
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};
