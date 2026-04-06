#include"GameExitButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<ISceneState> GameExitButton::ExePushButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}