#pragma once

#include"B_ButtonUI.h"

class ContinueStartButton : public B_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};