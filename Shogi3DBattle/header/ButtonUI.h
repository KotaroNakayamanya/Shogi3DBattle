#pragma once

#include"IButtonUI.h"

class ButtonUI : public IButtonUI
{
private:
    D2D1_RECT_F              _rect;         // UI範囲
    std::vector<TextAndRect> _textAndRects; // テキスト及び描画範囲
    bool                     _isSelected;   // ボタンUI選択状態

public:
    virtual std::unique_ptr<ISceneState> ExePushButton() = 0; // ボタン押下処理

    void        SetRect(D2D1_RECT_F rect) override {_rect = rect;} // UI範囲セット
    D2D1_RECT_F GetRect()                 override {return _rect;} // UI範囲を返す
    void                     SetTextAndRects(std::vector<TextAndRect> tr) override {_textAndRects = tr;}   // テキスト及び描画範囲セット
    std::vector<TextAndRect> GetTextAndRects()                            override {return _textAndRects;} // テキスト及び描画範囲を返す
    void SetIsSelected(bool select) override {_isSelected = select;} // 選択状態セット
    bool IsSelected   ()            override {return _isSelected;  } // 選択状態を返す

    ButtonUI() : _isSelected(false){}
};