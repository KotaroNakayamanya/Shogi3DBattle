#pragma once

#include"I_SceneState.h"
#include"I_Button.h"

class I_SelectingButtonScene : public I_SceneState
{
private:
    I_Button* _selectedButton; // 選択されているボタン
    bool      _isSetButton;    // ボタンがセットされているか判定

protected:
    std::unique_ptr<I_SceneState> ExeDecisionButtonProcess(); // 決定ボタン処理
    I_Button* GetSelectedButton(); // 選択されているボタンを返す

    virtual void SetButton() = 0; // ボタンUIセット

    // ボタン選択シーン動作
    virtual std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) = 0;

public:
    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSceneProcess(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    I_SelectingButtonScene();
    virtual ~I_SelectingButtonScene() = default;
};