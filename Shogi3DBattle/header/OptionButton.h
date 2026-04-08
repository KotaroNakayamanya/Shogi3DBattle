#pragma once

#include"B_ButtonUI.h"

class OptionButton : public B_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // オプションボタン押下処理
};