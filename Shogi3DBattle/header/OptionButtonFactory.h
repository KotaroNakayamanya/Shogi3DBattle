#pragma once

#include"I_ButtonUIFactory.h"

class OptionButtonFactory : public I_ButtonUIFactory
{
public:
    std::unique_ptr<I_ButtonUI> CreateButtonUI( // オプションボタン作成
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) override;
};
