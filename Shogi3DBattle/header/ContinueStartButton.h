#pragma once

#include"I_TextButton.h"

class ContinueStartButton : public I_TextButton
{
public:
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override; // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—

    ContinueStartButton(
        D2D1_RECT_F         rect,
        std::vector<TextUI*> textAndRects); 
};