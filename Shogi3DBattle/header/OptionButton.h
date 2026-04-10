#pragma once

#include"I_ButtonUI.h"

class OptionButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // オプションボタン押下処理

    OptionButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects); 
};