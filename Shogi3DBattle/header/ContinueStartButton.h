#pragma once

#include"ButtonUI.h"

class ContinueStartButton : public ButtonUI
{
public:
    std::unique_ptr<ISceneState> ExePushButton() override; // ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};