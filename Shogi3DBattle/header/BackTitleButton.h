#pragma once

#include"I_TextButton.h"

class BackTitleButton : public I_TextButton
{
public:
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override; // タイトルにもどるボタン押下処理

    BackTitleButton(
        D2D1_RECT_F          rect,
        std::vector<TextUI*> textUIs); 
};
