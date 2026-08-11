#pragma once

#include"I_TextButton.h"
#include"I_Piece.h"

class PromotionButton : public I_TextButton
{
private:
    I_Piece*      _piece;  // 成り対象の駒
    unsigned char _row;    // 行
    unsigned char _column; // 列

public:
    // 成り実行ボタンの処理実行
    std::unique_ptr<I_SceneState> ExePushButtonProcess() override;

    PromotionButton(
        D2D1_RECT_F          rect,
        std::vector<TextUI*> textUIs,
        I_Piece*             piece,
        unsigned char        row,
        unsigned char        column); 
};