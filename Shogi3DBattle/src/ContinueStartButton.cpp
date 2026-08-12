#include"ContinueStartButton.h"
#include"SelectingPieceScene.h"
#include"Application.h"
// つづきからボタン押下処理
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButtonProcess()
{
    // 活性状態なら駒選択シーンに遷移
    if (GetIsActive())
    {
        return std::make_unique<SelectingPieceScene>();
    }
    else
    {
        return nullptr;
    }
}


ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_TextButton(rect, textUIs, false)
{
    // ゲーム途中なら活性化
    auto& app = Application::GetInstance();
    if (app.GetIsProgress())
    {
        SetIsActive(true);
    }
}