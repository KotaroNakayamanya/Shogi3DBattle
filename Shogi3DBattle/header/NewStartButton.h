#pragma once

#include"ButtonUI.h"

class NewStartButton : public ButtonUI
{
public:
    std::unique_ptr<ISceneState> ExePushButton() override; // ‚Í‚¶‚ß‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};