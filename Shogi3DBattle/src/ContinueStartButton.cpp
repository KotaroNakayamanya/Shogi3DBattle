#include"ContinueStartButton.h"

// つづきからボタン押下処理
std::unique_ptr<I_SceneState> ContinueStartButton::ExePushButton()
{
    return nullptr;
}

ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect)
    : ContinueStartButton(rect, std::vector<TextAndRect>()){}

ContinueStartButton::ContinueStartButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_textAndRects.size() == 0)
    {
        TextAndRect defaultText = {L"つづきから", _rect};
        _textAndRects.push_back(defaultText);
    }
}
