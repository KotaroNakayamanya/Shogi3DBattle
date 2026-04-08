#include"NewStartButton.h"
#include"Application.h"
#include"SelectingPiece.h"

// はじめからボタン押下処理
std::unique_ptr<I_SceneState> NewStartButton::ExePushButton()
{
    // 駒選択シーンに遷移
    auto newSceneState = std::make_unique<SelectingPiece>();

    // UI削除
    auto& app = Application::GetInstance();
    app.RemoveAllUI();

    // 左クリックを解除
    auto inputHandler = app.GetInputHandler();
    inputHandler->RemoveLClick();

    return newSceneState;
}