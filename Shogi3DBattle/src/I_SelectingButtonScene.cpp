#include"I_SelectingButtonScene.h"
#include"Application.h"

// 決定ボタン処理
std::unique_ptr<I_SceneState> I_SelectingButtonScene::ExeDecisionButtonProcess()
{
    // ボタンUIが選択されていればボタン処理実行、選択されていなければ何もしない
    return _selectedButton ?
        _selectedButton->ExePushButtonProcess() : nullptr;
}

I_Button* I_SelectingButtonScene::GetSelectedButton(){return _selectedButton;} // 選択されているボタンを返す

// ボタン選択シーン動作
std::unique_ptr<I_SceneState> I_SelectingButtonScene::ExeSceneProcess(
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

    if (_selectedButton) // ボタンが選択されていれば選択解除
    {
        _selectedButton->SetIsSelected(false);
        _selectedButton = nullptr;
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
            _selectedButton = buttonUI;

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
    : _isSetButton(false), _selectedButton(nullptr){}