#pragma once

#include"B_SceneState.h"
#include"Camera.h"
#include"I_ButtonUI.h"

class StartMenu : public B_SceneState
{
public:
    Camera*    _mainCamera;  // メインカメラ
    I_ButtonUI* _selectingButtonUI; // 選択しているボタンUI

    std::unique_ptr<I_SceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<I_SceneState> ExeCancelButton(); // キャンセルボタン処理

public:
    // スタートメニューシーン動作
    std::unique_ptr<I_SceneState> ExeSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    StartMenu();
    ~StartMenu();
};