#pragma once

#include"I_ButtonUI.h"

class ContinueStartButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—

    ContinueStartButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects); 
};