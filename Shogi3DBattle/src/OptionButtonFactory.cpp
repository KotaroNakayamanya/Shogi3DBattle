#include"OptionButtonFactory.h"
#include"OptionButton.h"

// オプションボタン作成
std::unique_ptr<I_ButtonUI> OptionButtonFactory::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    auto newStartButton = std::make_unique<OptionButton>();

    newStartButton->SetRect(rect);
    newStartButton->SetTextAndRects(textAndRects);

    return newStartButton;
}