#pragma once

#include"I_SelectingButtonScene.h"
#include"I_Piece.h"

class PromotionScene : public I_SelectingButtonScene
{
private:
    I_Piece* _piece;    // 成り対象の駒
    bool     _isForced; // 成り強制かどうか

    void SetButton() override; // ボタンUIセット

    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

public:
    PromotionScene(I_Piece* piece, bool forced);
};