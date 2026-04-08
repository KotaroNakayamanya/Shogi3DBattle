#include"GameExitButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<I_SceneState> GameExitButton::ExePushButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}