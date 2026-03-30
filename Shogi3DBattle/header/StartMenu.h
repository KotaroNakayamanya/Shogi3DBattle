#pragma once

#include"ISceneState.h"
#include"Camera.h"
#include"UIObj.h"

class StartMenu : public ISceneState
{
public:
    Camera* _mainCamera; // メインカメラ
    UIObj::UIType _selectingUI; // 選択しているUI

    ISceneState* ExeDecisionButton(); // 決定ボタン処理
    ISceneState* ExeCancelButton(); // キャンセルボタン処理

public:
    // スタートメニューシーン動作
    ISceneState* ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    StartMenu();
    ~StartMenu();
};