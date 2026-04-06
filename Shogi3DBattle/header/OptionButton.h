#pragma once

#include"ButtonUI.h"

class OptionButton : public ButtonUI
{
public:
    std::unique_ptr<ISceneState> ExePushButton() override; // オプションボタン押下処理
};