#pragma once

#include"UI.h"
#include"Text2D.h"
#include"I_SceneState.h"
#include<vector>

class I_ButtonUI : public UI
{
private:
    bool                     _isSelected;   // ボタンUI選択状態

protected:
    std::vector<Text2D> _text2Ds; // 2Dテキスト

public:
    virtual std::unique_ptr<I_SceneState> ExePushButton() = 0; // ボタン押下処理

    void                SetText2Ds(std::vector<Text2D> text2Ds); // 2Dテキストセット
    std::vector<Text2D> GetText2Ds();                           // ２Dテキストを返す

    void SetIsSelected(bool select); // 選択状態セット
    bool IsSelected();               // 選択状態を返す

    I_ButtonUI(D2D1_RECT_F rect, std::vector<Text2D> text2Ds = std::vector<Text2D>());
    virtual ~I_ButtonUI() = default;
};