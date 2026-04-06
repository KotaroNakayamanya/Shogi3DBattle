#pragma once

#include"ISceneState.h"
#include<vector>
#include"TextAndRectStruct.h"

class IButtonUI
{
public:
    virtual std::unique_ptr<ISceneState> ExePushButton() = 0; // ボタン押下処理

    virtual void        SetRect(D2D1_RECT_F rect) = 0; // UI範囲セット
    virtual D2D1_RECT_F GetRect()                 = 0; // UI範囲を返す
    virtual void                      SetTextAndRects(std::vector<TextAndRect> tr) = 0; // テキスト及び描画範囲セット
    virtual std::vector<TextAndRect>  GetTextAndRects()                            = 0; // テキスト及び描画範囲を返す
    virtual void SetIsSelected(bool select) = 0; // 選択状態セット
    virtual bool IsSelected   ()            = 0; // 選択状態を返す

    virtual ~IButtonUI() = default;
};