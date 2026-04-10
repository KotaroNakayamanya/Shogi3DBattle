#pragma once

#include"TextAndRectStruct.h"
#include"I_SceneState.h"
#include<vector>

class I_ButtonUI
{
private:
    D2D1_RECT_F              _rect;         // UI範囲
    std::vector<TextAndRect> _textAndRects; // テキスト及び描画範囲
    bool                     _isSelected;   // ボタンUI選択状態

public:
    virtual std::unique_ptr<I_SceneState> ExePushButton() = 0; // ボタン押下処理

    void        SetRect(D2D1_RECT_F rect); // UI範囲セット
    D2D1_RECT_F GetRect();                 // UI範囲を返す

    void                     SetTextAndRects(std::vector<TextAndRect> tr); // テキスト及び描画範囲セット
    std::vector<TextAndRect> GetTextAndRects();                            // テキスト及び描画範囲を返す

    void SetIsSelected(bool select); // 選択状態セット
    bool IsSelected();               // 選択状態を返す

    I_ButtonUI() : _isSelected(false){}
    virtual ~I_ButtonUI() = default;
};