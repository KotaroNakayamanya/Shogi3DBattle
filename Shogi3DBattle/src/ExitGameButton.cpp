#include"ExitGameButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<I_SceneState> ExitGameButton::ExePushButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}

ExitGameButton::ExitGameButton(
    D2D1_RECT_F         rect,
    std::vector<Text2D> text2Ds)
    : I_ButtonUI(rect, text2Ds)
{
    // テキストがなければデフォルトテキストを追加
    if (_text2Ds.size() == 0)
    {
        Text2D defaultText = {L"ゲーム終了", _rect};
        _text2Ds.push_back(defaultText);
    }
}