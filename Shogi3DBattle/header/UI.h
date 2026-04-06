#pragma once

#include"UIType.h"
#include<string>
#include<d2d1_3.h>

class UI
{
private:
    const std::wstring _text;       // テキスト
    const UIType       _uiType;     // UIタイプ

    D2D1_RECT_F  _rect;       // テキスト範囲
    bool         _isSelected; // 選択状態

    UI() = default;

public:
    std::wstring GetText();   // テキストを返す
    UIType       GetUIType(); // UIタイプを返す

    void         SetRect(D2D1_RECT_F rect); // テキスト範囲セット
    D2D1_RECT_F  GetRect();                 // テキスト範囲を返す
    void         SetIsSelected(bool state); // 選択状態セット
    bool         IsSelected();              // 選択状態を返す

    UI(std::wstring text, D2D1_RECT_F rect, UIType uiType)
        : _text(text), _rect(rect), _uiType(uiType), _isSelected(false){}
    ~UI() = default;
};