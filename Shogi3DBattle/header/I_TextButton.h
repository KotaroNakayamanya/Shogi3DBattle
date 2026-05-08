#pragma once

#include"I_Button.h"

class I_TextButton : public I_Button
{
private:
    std::vector<TextUI*> _textUIs;    // ボタンに関連しているテキストUI

public:
    void ExeSelectedStateProcess() override; // 選択状態に合わせた処理実行

    void                 SetTextUIs(std::vector<TextUI*> textUIs); // ボタンに関連しているテキストUIセット
    std::vector<TextUI*> GetTextUIs();                             // ボタンに関連しているテキストUIを返す

    I_TextButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs = std::vector<TextUI*>());
    virtual ~I_TextButton() = default;
};