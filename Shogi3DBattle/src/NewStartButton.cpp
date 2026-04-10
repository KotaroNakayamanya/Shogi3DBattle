#include"NewStartButton.h"
#include"Application.h"
#include"SelectingPiece.h"

// はじめからボタン押下処理
std::unique_ptr<I_SceneState> NewStartButton::ExePushButton()
{
    // 駒選択シーンに遷移
    auto newSceneState = std::make_unique<SelectingPiece>();

    // UI削除
    auto& app = Application::GetInstance();
    app.RemoveAllUI();

    // 左クリックを解除
    auto inputHandler = app.GetInputHandler();
    inputHandler->RemoveLClick();

    return newSceneState;
}

NewStartButton::NewStartButton(D2D1_RECT_F rect)
    : NewStartButton(rect, std::vector<TextAndRect>()){}

NewStartButton::NewStartButton(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : I_ButtonUI(rect, textAndRects)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_textAndRects.size() == 0)
    {
        TextAndRect defaultText = {L"はじめから", _rect};
        _textAndRects.push_back(defaultText);
    }
}

