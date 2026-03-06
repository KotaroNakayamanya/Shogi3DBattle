#pragma once

class Command;

class SceneState
{
public:
    virtual SceneState* ExeUpCommand()    = 0; // 上
    virtual SceneState* ExeLeftCommand()  = 0; // 左 
    virtual SceneState* ExeDownCommand()  = 0; // 下
    virtual SceneState* ExeRightCommand() = 0; // 右

    virtual SceneState* ExeMouseCommand() = 0; // マウス操作

    virtual SceneState* ExeDecisionCommand() = 0; // 決定
    virtual SceneState* ExeCancelCommand()   = 0; // キャンセル

    SceneState()  = default;
    ~SceneState() = default;
};