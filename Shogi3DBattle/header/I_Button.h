#pragma once

#include"UI.h"
#include"TextUI.h"
#include"Text2D.h"
#include"I_SceneState.h"
#include<vector>

class I_Button : public UI
{
private: 
    bool _isSelected; // ボタン選択状態

public:
    virtual void                          ExeSelectedStateProcess() = 0; // 選択状態に合わせた処理実行
    virtual std::unique_ptr<I_SceneState> ExePushButtonProcess   () = 0; // ボタン押下処理

    void                 SetIsSelected(bool select); // 選択状態セット
    bool                 IsSelected   ();            // 選択状態を返す

    I_Button(D2D1_RECT_F rect);
    virtual ~I_Button() = default;
};