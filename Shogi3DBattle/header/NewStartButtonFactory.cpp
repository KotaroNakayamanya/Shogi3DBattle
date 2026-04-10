#include"NewStartButtonFactory.h"
#include"NewStartButton.h"

// ÇÕÇ∂ÇﬂÇ©ÇÁÉ{É^ÉìçÏê¨
std::unique_ptr<I_ButtonUI> NewStartButtonFactory::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    auto uniquePtr = textAndRects.size() == 0 ?
        std::make_unique<NewStartButton>(rect) : std::make_unique<NewStartButton>(rect, textAndRects);

    return uniquePtr;
}