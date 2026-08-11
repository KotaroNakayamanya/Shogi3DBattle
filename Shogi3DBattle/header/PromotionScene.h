#pragma once

#include"I_SelectingButtonScene.h"
#include"I_Piece.h"

class PromotionScene : public I_SelectingButtonScene
{
private:
    I_Piece*      _piece;    // 成り対象の駒
    unsigned char _row;      // 行
    unsigned char _column;   // 列
    bool          _isForced; // 成り強制かどうか

    void SetButton() override; // ボタンUIセット

    // ボタン選択シーン動作
    std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

public:
    PromotionScene(I_Piece* piece, unsigned char row, unsigned char column, bool forced);
};