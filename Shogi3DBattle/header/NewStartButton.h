#pragma once

#include"I_TextButton.h"

class NewStartButton : public I_TextButton
{
public:
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override; // ‚Í‚¶‚ß‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—

    NewStartButton(
        D2D1_RECT_F          rect,
        std::vector<TextUI*> textUIs); 
};