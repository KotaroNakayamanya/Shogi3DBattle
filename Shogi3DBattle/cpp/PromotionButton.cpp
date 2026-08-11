#include"PromotionButton.h"
#include"SetMovingPieceScene.h"

// 成り実行ボタンの処理実行
std::unique_ptr<I_SceneState> PromotionButton::ExePushButtonProcess()
{
    // 駒を成り状態にする
    _piece->SetIsPromotion(true);

    //// 裏返しにする
    //// ワールド行列を修正してひっくり返す
    //auto worldMat = _piece->GetWorldMat();
    //auto mat      = worldMat->GetMat();
    //mat *= DirectX::XMMatrixRotationY(DirectX::XM_PIDIV4);
    //worldMat->SetMat(mat);

    // 駒の動きをセットするシーンに遷移
    return std::make_unique<SetMovingPieceScene>(_piece, _row, _column);
}

PromotionButton::PromotionButton(
    D2D1_RECT_F          rect,
    std::vector<TextUI*> textUIs,
    I_Piece*             piece,
    unsigned char        row,
    unsigned char        column) 
    : I_TextButton(rect, textUIs), _piece(piece), _row(row), _column(column){}
