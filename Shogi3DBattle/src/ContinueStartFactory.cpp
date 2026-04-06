#include"ContinueStartButtonFactory.h"
#include"ContinueStartButton.h"

// ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“ì¬
std::unique_ptr<IButtonUI> ContinueStartButtonFactory::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    auto newStartButton = std::make_unique<ContinueStartButton>();

    newStartButton->SetRect(rect);
    newStartButton->SetTextAndRects(textAndRects);

    return newStartButton;
}