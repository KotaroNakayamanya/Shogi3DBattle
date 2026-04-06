#pragma once

#include"ISceneState.h"
#include"Camera.h"
#include"IButtonUI.h"

class StartMenu : public ISceneState
{
public:
    Camera*    _mainCamera;  // メインカメラ
    IButtonUI* _selectingButtonUI; // 選択しているボタンUI

    std::unique_ptr<ISceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<ISceneState> ExeCancelButton(); // キャンセルボタン処理

public:
    // スタートメニューシーン動作
    std::unique_ptr<ISceneState> ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    StartMenu();
    ~StartMenu();
};