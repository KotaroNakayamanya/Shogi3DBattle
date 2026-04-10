#pragma once

#include"I_ButtonUI.h"

class OptionButton : public I_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // オプションボタン押下処理
};