#include"I_SelectingButtonScene.h"
#include"Application.h"

// ボタン選択シーン動作
std::unique_ptr<I_SceneState> I_SelectingButtonScene::ExeSceneOperation(
    unsigned char inputMemory,
    int           cursorX,
    int           cursorY,
    int           cursorXMove,
    int           cursorYMove)
{
    if (!_isSetButton) // ボタンUIがセットされていなければセット
    {
        SetButton();
        _isSetButton = true;
    }

    if (_selectingButton) // ボタンが選択されていれば選択解除
    {
        _selectingButton->SetIsSelected(false);
        _selectingButton = nullptr;
    }

    // 選択されているボタンを探す（後から追加されているボタンを優先して選択状態にする）
    auto buttonUIs = Application::GetInstance().GetButtons();
    for (auto it = buttonUIs.rbegin(); it < buttonUIs.rend(); it++)
    {
        auto buttonUI = *it;
        auto rect = buttonUI->GetRect();

        // ボタンUIの範囲にカーソルがあるか判定
        bool isCursorInWidthRange  = rect.left <= cursorX && cursorX <= rect.right;
        bool isCursorInHeightRange = rect.top  <= cursorY && cursorY <= rect.bottom;
        bool isSelected = isCursorInWidthRange && isCursorInHeightRange;

        if (isSelected) // 選択されていれば選択状態にし、break
        {
            buttonUI->SetIsSelected(true);
            _selectingButton = buttonUI;

            break;
        }
    }

    // ボタン選択シーン動作
    return ExeSelectingButtonSceneOperation(
        inputMemory,
        cursorX,
        cursorY,
        cursorXMove,
        cursorYMove);
}


I_SelectingButtonScene::I_SelectingButtonScene()
    : _isSetButton(false), _selectingButton(nullptr){}