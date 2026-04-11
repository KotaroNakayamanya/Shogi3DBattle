#pragma once

#include"I_ButtonUI.h"

class ExitGameButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ゲーム終了ボタン押下処理

    ExitGameButton(
        D2D1_RECT_F         rect,
        std::vector<Text2D> textAndRects = std::vector<Text2D>()); 
};