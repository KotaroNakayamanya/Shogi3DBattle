#include"GameExitButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<I_SceneState> GameExitButton::ExePushButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}

GameExitButton::GameExitButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects){}