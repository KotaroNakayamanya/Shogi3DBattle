#include"PromotionScene.h"
#include"Application.h"
#include"RuleManager.h"
#include"SetMovingPieceScene.h"

// ボタンUIセット
void PromotionScene::SetButton()
{
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    auto uiWidth  = windowWidth  / 6; // UIの横の長さ
    auto uiHeight = windowHeight / 9; // UIの縦の長さ
    
    
    float left   = (windowWidth - uiWidth) / 2; // UI左位置　中央揃えのため調整
    float right  = left + uiWidth;              // UI右位置　UI左位置に横の長さを足す
    float bottom = windowHeight / 2.0f;         // UI下位置
    float top    = bottom - uiHeight;           // UI上位置

    float heightOffset = uiHeight + 10.0f; // ボタンUIを追加するごとに縦にずらす数値
    bottom -= 5.0f;
    top    -= 5.0f;

    D2D1_RECT_F rect; // ボタンUI範囲

    // 駒成りボタン
    rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::PIECE_PROMOTION_BUTTON, rect, _piece, _row, _column);

    // 駒成らずボタン
    top    += heightOffset;
    bottom += heightOffset;
    rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::PIECE_NOT_PROMOTION_BUTTON, rect, _piece, _row, _column);
}

// ボタン選択シーン動作
std::unique_ptr<I_SceneState> PromotionScene::ExeSelectingButtonSceneOperation(
    unsigned char inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    std::unique_ptr<I_SceneState> newSceneState = nullptr;

    if (inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButtonProcess();

    return newSceneState;
}

PromotionScene::PromotionScene(I_Piece* piece, unsigned char row, unsigned char column)
    : _piece(piece), _row(row), _column(column){}