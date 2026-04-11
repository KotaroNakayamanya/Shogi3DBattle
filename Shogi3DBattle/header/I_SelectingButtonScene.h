#pragma once

#include"I_SceneState.h"
#include"I_ButtonUI.h"

class I_SelectingButtonScene : public I_SceneState
{
protected:
    bool        _isSetButtonUI;   // UIがセットされているか判定
    I_ButtonUI* _selectingButton; // 選択しているボタン

    virtual void SetButtonUI() = 0; // ボタンUIセット

    // ボタン選択シーン動作
    virtual std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) = 0;

public:
    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    I_SelectingButtonScene();
    virtual ~I_SelectingButtonScene() = default;
};