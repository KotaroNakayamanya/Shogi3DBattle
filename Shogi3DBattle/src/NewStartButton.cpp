#include"NewStartButton.h"
#include"Application.h"
#include"SelectingPieceScene.h"

// はじめからボタン押下処理
std::unique_ptr<I_SceneState> NewStartButton::ExePushButtonProcess()
{
    // ゲームの状態を初期化
    auto& app = Application::GetInstance();
    app.InitGameState();

    // ゲーム途中であることをセット
    app.SetIsProgress(true);

    // 駒選択シーンに遷移
    auto newSceneState = std::make_unique<SelectingPieceScene>();

    return newSceneState;
}

NewStartButton::NewStartButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs, true){}