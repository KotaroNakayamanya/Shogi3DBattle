#include"OptionButton.h"
#include"Application.h"

// オプションボタン押下処理
std::unique_ptr<I_SceneState> OptionButton::ExePushButtonProcess()
{
    return nullptr;
}

OptionButton::OptionButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs){}