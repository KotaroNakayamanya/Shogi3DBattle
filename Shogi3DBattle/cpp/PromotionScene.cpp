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

    auto uiWidth  = windowWidth  / 5; // UIの横の長さ
    auto uiHeight = windowHeight / 9; // UIの縦の長さ
    
    
    float left = (windowWidth - uiWidth) / 2; // UI左位置　中央揃えのため調整
    float top  = windowHeight / 1.9f;         // UI上位置　真ん中よりちょっと下
    float right = left + uiWidth;             // UI右位置　UI左位置に横の長さを足す
    float bottom = top + uiHeight;            // UI下位置　UI上位置に縦の長さを足す

    float heightOffset = uiHeight + 3.0f; // ボタンUIを追加するごとに縦にずらす数値

    D2D1_RECT_F rect; // ボタンUI範囲

    // 駒成りボタン
    rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::PIECE_PROMOTION_BUTTON, rect, _piece, _row, _column);

    // 駒成らずボタン
    top    += uiHeight;
    bottom += uiHeight;
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