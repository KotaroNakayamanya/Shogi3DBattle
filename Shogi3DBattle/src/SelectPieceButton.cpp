#include"SelectPieceButton.h"
#include"MovingPieceScene.h"
#include"Application.h"
#include"RuleManager.h"

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
    // 駒が動かせるのであれば選択可能、動かせないのであれば選択不可
    auto piece = GetPiece();

    if (RuleManager::GetCanMove(piece))
    {
        return std::make_unique<MovingPieceScene>(GetPiece());
    }
    else
    {
        return nullptr;
    }
}

SelectPieceButton::SelectPieceButton(D2D1_RECT_F rect, I_Piece* piece)
    : I_PieceButton(rect, piece){}