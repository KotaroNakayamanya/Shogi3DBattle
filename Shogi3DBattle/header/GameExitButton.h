#pragma once

#include"I_ButtonUI.h"

class GameExitButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ゲーム終了ボタン押下処理

    GameExitButton(D2D1_RECT_F rect); 
    GameExitButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects); 
};