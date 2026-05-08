#include"ExitGameButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<I_SceneState> ExitGameButton::ExePushButtonProcess()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}

ExitGameButton::ExitGameButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs){}