#pragma once

#include"ButtonUI.h"

class GameExitButton : public ButtonUI
{
public:
    std::unique_ptr<ISceneState> ExePushButton() override; // ゲーム終了ボタン押下処理
};