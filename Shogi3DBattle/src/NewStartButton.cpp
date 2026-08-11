#include"NewStartButton.h"
#include"Application.h"
#include"SelectingPieceScene.h"

// はじめからボタン押下処理
std::unique_ptr<I_SceneState> NewStartButton::ExePushButtonProcess()
{
    auto& app = Application::GetInstance();

    // 駒の位置を初期化
    auto piecePosManager = app.GetPiecePosManager();
    piecePosManager->InitPiecesPos();

    // プレイヤー側の初期処理
    app.SetCurrentPlayerTurn(PlayerSide::PLAYER_1);
    app.SetIsPlayerWinning(PlayerSide::PLAYER_1, false);
    app.SetIsPlayerWinning(PlayerSide::PLAYER_2, false);
    app.SetIsPlayerChecked(PlayerSide::PLAYER_1, false);
    app.SetIsPlayerChecked(PlayerSide::PLAYER_2, false);

    // 駒選択シーンに遷移
    auto newSceneState = std::make_unique<SelectingPieceScene>();

    return newSceneState;
}

NewStartButton::NewStartButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs){}