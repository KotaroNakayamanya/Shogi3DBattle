#include"OptionButton.h"

// オプションボタン押下処理
std::unique_ptr<I_SceneState> OptionButton::ExePushButton()
{
    return nullptr;
}

OptionButton::OptionButton(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_textAndRects.size() == 0)
    {
        TextAndRect defaultText = {L"オプション", _rect};
        _textAndRects.push_back(defaultText);
    }
}