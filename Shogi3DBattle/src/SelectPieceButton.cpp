#include"SelectPieceButton.h"
#include"MovingPieceScene.h"
#include"Application.h"

// 選択状態に合わせた処理実行
void SelectPieceButton::ExeSelectedStateProcess()
{
    if(IsSelected())
    {
        auto textures = Application::GetInstance().GetTextures();
        textures->CreateCanMoveEffectTextures(GetPiece());
    }
    else
    {

    }
}

// ボタン押下処理実行
std::unique_ptr<I_SceneState> SelectPieceButton::ExePushButtonProcess()
{
    return std::make_unique<MovingPieceScene>(GetPiece());
}

SelectPieceButton::SelectPieceButton(D2D1_RECT_F rect, I_Piece* piece)
    : I_PieceButton(rect, piece){}