#pragma once

#include"B_ButtonUI.h"

class GameExitButton : public B_ButtonUI
{
public:
    std::unique_ptr<I_SceneState> ExePushButton() override; // ゲーム終了ボタン押下処理
};