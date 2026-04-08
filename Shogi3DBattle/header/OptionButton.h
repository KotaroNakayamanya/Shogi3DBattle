#pragma once

#include"ButtonUI.h"

class OptionButton : public ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // オプションボタン押下処理
};