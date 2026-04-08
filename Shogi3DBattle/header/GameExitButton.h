#pragma once

#include"ButtonUI.h"

class GameExitButton : public ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ゲーム終了ボタン押下処理
};