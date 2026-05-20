#include"ContinueStartButton.h"
#include"SelectingPieceScene.h"

// つづきからボタン押下処理
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButtonProcess()
{
    // 駒選択シーンに遷移
    auto newSceneState = std::make_unique<SelectingPieceScene>();

    return newSceneState;
}

ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs){}