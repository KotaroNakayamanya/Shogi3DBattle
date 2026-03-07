#pragma once

#include<Windows.h>
#include"ISceneState.h"

class MovePiece : public ISceneState
{
private:
    HWND _hwnd;
public:
    virtual ISceneState* ExeDecision() override; // 決定
    virtual ISceneState* ExeCancel()   override; // キャンセル

    virtual ISceneState* ExeUp()    override; // 上
    virtual ISceneState* ExeLeft()  override; // 左 
    virtual ISceneState* ExeDown()  override; // 下
    virtual ISceneState* ExeRight() override; // 右

    virtual ISceneState* ExeMouseMove() override; // マウス操作

    MovePiece(HWND hwnd);
    MovePiece();
    ~MovePiece();
};