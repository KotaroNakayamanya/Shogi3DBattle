#pragma once

#include"B_ButtonUI.h"

class NewStartButton : public B_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ‚Í‚¶‚ß‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};