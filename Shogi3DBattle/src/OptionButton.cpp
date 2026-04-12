#include"OptionButton.h"
#include"Application.h"

// オプションボタン押下処理
std::unique_ptr<I_SceneState> OptionButton::ExePushButton()
{
    return nullptr;
}

OptionButton::OptionButton(
    D2D1_RECT_F         rect,
    std::vector<Text2D> text2Ds)
    : I_ButtonUI(rect, text2Ds)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_text2Ds.size() == 0)
    {
        Text2D defaultText;
        defaultText.text       = L"オプション";
        defaultText.textFormat = GetDefaultTextFormat();
        defaultText.brush      = GetDefaultBrush();
        defaultText.rect       = _rect;

        _text2Ds.push_back(defaultText);
    }
}