#include"ContinueStartButton.h"
#include"Application.h"

// つづきからボタン押下処理
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButton()
{
    return nullptr;
}

ContinueStartButton::ContinueStartButton(
    D2D1_RECT_F         rect,
    std::vector<Text2D> text2Ds)
    : I_ButtonUI(rect, text2Ds)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_text2Ds.size() == 0)
    {
        auto dx12 = Application::GetInstance().GetDX12();

        Text2D defaultText;
        defaultText.text = L"つづきから";
        defaultText.brush = dx12->GetBrackBrush();
        defaultText.rect = _rect;

        _text2Ds.push_back(defaultText);
    }
}