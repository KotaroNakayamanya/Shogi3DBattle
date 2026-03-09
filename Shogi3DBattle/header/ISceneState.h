#pragma once

#include<memory>

class ISceneState
{
public:
    virtual ISceneState* ExeDecisionButton() = 0;  // 決定ボタン処理
    virtual ISceneState* ExeCancelButton()   = 0;  // キャンセルボタン処理
    virtual ISceneState* ExeCursorOperation() = 0; // カーソル操作処理

    virtual ISceneState* ExeUpButton()    = 0; // 上ボタン処理
    virtual ISceneState* ExeLeftButton()  = 0; // 左ボタン処理
    virtual ISceneState* ExeDownButton()  = 0; // 下ボタン処理
    virtual ISceneState* ExeRightButton() = 0; // 右ボタン処理

    ISceneState()  = default;
    ~ISceneState(){}
};