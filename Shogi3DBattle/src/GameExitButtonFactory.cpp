#include"GameExitButtonFactory.h"
#include"GameExitButton.h"

// ゲーム終了ボタン作成
std::unique_ptr<I_ButtonUI> GameExitButtonFactory::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    auto newStartButton = std::make_unique<GameExitButton>();

    newStartButton->SetRect(rect);
    newStartButton->SetTextAndRects(textAndRects);

    return newStartButton;
}