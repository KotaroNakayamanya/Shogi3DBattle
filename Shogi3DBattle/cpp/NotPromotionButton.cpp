#include"NotPromotionButton.h"
#include"SetMovingPieceScene.h"

// 成らずボタンの処理実行
std::unique_ptr<I_SceneState> NotPromotionButton::ExePushButtonProcess()
{
    // 駒の動きをセットするシーンに遷移
    return std::make_unique<SetMovingPieceScene>(_piece, _row, _column);
}

NotPromotionButton::NotPromotionButton(
    D2D1_RECT_F          rect,
    std::vector<TextUI*> textUIs,
    I_Piece*             piece,
    unsigned char        row,
    unsigned char        column) 
    : I_TextButton(rect, textUIs), _piece(piece), _row(row), _column(column){}
