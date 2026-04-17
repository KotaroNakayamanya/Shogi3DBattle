#pragma once

#include"I_SelectingButtonScene.h"
#include"Camera.h"
#include"I_ButtonUI.h"

class TitleMenu : public I_SelectingButtonScene
{
private:
    Camera* _mainCamera;  // メインカメラ
    bool    _isSetTextUI; // テキストUIセットチェック
    
    void SetTextUI();            // テキストUIセット
    void SetButtonUI() override; // ボタンUIセット

    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    std::unique_ptr<I_SceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<I_SceneState> ExeCancelButton();   // キャンセルボタン処理

public:
    TitleMenu();
};