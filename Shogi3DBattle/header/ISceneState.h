#pragma once

class Command;

class ISceneState
{
public:
    virtual ISceneState* ExeDecision() = 0; // 決定
    virtual ISceneState* ExeCancel()   = 0; // キャンセル

    virtual ISceneState* ExeUp()    = 0; // 上
    virtual ISceneState* ExeLeft()  = 0; // 左 
    virtual ISceneState* ExeDown()  = 0; // 下
    virtual ISceneState* ExeRight() = 0; // 右

    virtual ISceneState* ExeMouseMove() = 0; // マウス操作

    ISceneState()  = default;
    ~ISceneState(){}
};