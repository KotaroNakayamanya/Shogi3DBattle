#pragma once

#include"I_TextButton.h"

class OptionButton : public I_TextButton
{
public:
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override; // オプションボタン押下処理

    OptionButton(
        D2D1_RECT_F         rect,
        std::vector<TextUI*> textAndRects);
};