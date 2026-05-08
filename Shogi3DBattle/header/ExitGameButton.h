#pragma once

#include"I_TextButton.h"

class ExitGameButton : public I_TextButton
{
public:
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override; // ゲーム終了ボタン押下処理

    ExitGameButton(
        D2D1_RECT_F         rect,
        std::vector<TextUI*> textAndRects); 
};