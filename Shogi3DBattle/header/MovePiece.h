#pragma once

#include<Windows.h>
#include"SceneState.h"

class MovePiece : public SceneState
{
private:
    HWND _hwnd;
public:
    virtual SceneState* ExeUpCommand()    override; // 上
    virtual SceneState* ExeLeftCommand()  override; // 左 
    virtual SceneState* ExeDownCommand()  override; // 下
    virtual SceneState* ExeRightCommand() override; // 右

    virtual SceneState* ExeMouseCommand() override; // マウス操作

    virtual SceneState* ExeDecisionCommand() override; // 決定
    virtual SceneState* ExeCancelCommand()   override; // キャンセル

    MovePiece(HWND hwnd);
    MovePiece();
    ~MovePiece();
};