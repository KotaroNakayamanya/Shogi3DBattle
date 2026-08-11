#include"PromotionScene.h"
#include"InputHandler.h"

// ボタンUIセット
void PromotionScene::SetButton()
{

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

PromotionScene::PromotionScene(I_Piece* piece, bool forced) : _piece(piece), _isForced(forced){}