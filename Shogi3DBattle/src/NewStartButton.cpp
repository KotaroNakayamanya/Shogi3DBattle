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

NewStartButton::NewStartButton(
    D2D1_RECT_F         rect,
    std::vector<Text2D> text2Ds)
    : I_ButtonUI(rect, text2Ds)
{
    // テキストの指定がなければデフォルトテキストを追加
    if (_text2Ds.size() == 0)
    {
        Text2D defaultText;
        defaultText.text = L"はじめから";
        defaultText.rect = _rect;

        _text2Ds.push_back(defaultText);
    }
}