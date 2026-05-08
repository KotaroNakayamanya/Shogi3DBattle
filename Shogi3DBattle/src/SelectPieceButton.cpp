#include"SelectPieceButton.h"
#include"MovingPiece.h"

// 選択状態に合わせた処理実行
void SelectPieceButton::ExeSelectedStateProcess()
{
    if(IsSelected()) ;
    else             ;
}

// ボタン押下処理実行
std::unique_ptr<I_SceneState> SelectPieceButton::ExePushButtonProcess()
{
    return std::make_unique<MovingPiece>(GetPiece());
}