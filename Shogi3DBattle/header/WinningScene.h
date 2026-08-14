#pragma once

#include"I_SelectingButtonScene.h"
#include"PlayerSide.h"

class WinningScene : public I_SelectingButtonScene
{
private:
    PlayerSide _winningPlayer; // 勝ったプレイヤー
    bool       _isSetTextUI;   // テキストUIセットチェック

    void SetTextUI();          // テキストUIセット
    void SetButton() override; // ボタンセット

    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

public:
    WinningScene(PlayerSide playerSide);
};