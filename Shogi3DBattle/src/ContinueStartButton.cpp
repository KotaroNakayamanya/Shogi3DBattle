#include"ContinueStartButton.h"
#include"Application.h"

// ‚Â‚Ã‚«‚©‚çƒ{ƒ^ƒ“‰Ÿ‰ºˆ—
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButtonProcess()
{
    return nullptr;
}

ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs){}