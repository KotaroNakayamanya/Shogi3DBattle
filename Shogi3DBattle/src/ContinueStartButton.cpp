#include"ContinueStartButton.h"

// ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButton()
{
    return nullptr;
}

ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects){}