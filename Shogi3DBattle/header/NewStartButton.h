#pragma once

#include"I_ButtonUI.h"

class NewStartButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ‚Í‚¶‚ß‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
};