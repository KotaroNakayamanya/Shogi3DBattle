#include"BackTitleButton.h"
#include"Application.h"
#include"TitleScene.h"

// タイトルに戻るボタン押下処理
std::unique_ptr<I_SceneState> BackTitleButton::ExePushButtonProcess()
{
    // タイトルシーンに遷移
    return std::make_unique<TitleScene>();
}

BackTitleButton::BackTitleButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs, true){}