#include"GameExitButton.h"
#include"Application.h"

// ゲーム終了ボタン押下処理
std::unique_ptr<I_SceneState> GameExitButton::ExePushButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());

    return nullptr;
}
GameExitButton::GameExitButton(D2D1_RECT_F rect)
    : GameExitButton(rect, std::vector<TextAndRect>()){}

GameExitButton::GameExitButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects)
{
    // テキストがなければデフォルトテキストを追加
    if (_textAndRects.size() == 0)
    {
        TextAndRect defaultText = {L"ゲーム終了", _rect};
        _textAndRects.push_back(defaultText);
    }
}
