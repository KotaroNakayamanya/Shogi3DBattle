#pragma once

#include"ButtonUI.h"

class ContinueStartButton : public ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};