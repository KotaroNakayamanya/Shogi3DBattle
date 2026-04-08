#include"NewStartButtonFactory.h"
#include"NewStartButton.h"

// ÇÕÇ∂ÇﬂÇ©ÇÁÉ{É^ÉìçÏê¨
std::unique_ptr<I_ButtonUI> NewStartButtonFactory::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    auto newStartButton = std::make_unique<NewStartButton>();

    newStartButton->SetRect(rect);
    newStartButton->SetTextAndRects(textAndRects);

    return newStartButton;
}