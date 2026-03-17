#pragma once

#include"IsceneState.h"
#include"KeyConf.h"

class InputHandler
{
private:
    std::unique_ptr<ISceneState> _sceneState; // シーンステート
    std::unique_ptr<KeyConf> _keyConf; // キーコンフィグ

    unsigned char _inputMemory = 0; // 入力記録
    int _cursorX; // カーソル横位置
    int _cursorY; // カーソル縦位置
    int _cursorXMove; // カーソル横移動距離
    int _cursorYMove; // カーソル縦移動距離

    void CheckUpdateSceneState(ISceneState* sceneState); // シーンステート更新チェック
    void SetSceneState(ISceneState* sceneState); // シーンステート更新

public:
    void ExeOperation(); // 操作開始

    void MemoryLClick(); // 左クリック記録
    void RemoveLClick(); // 左クリック解除
    void MemoryRClick(); // 右クリック記録
    void RemoveRClick(); // 右クリック解除
    void MemoryInputKey(WPARAM inputKey); // キー入力記録
    void RemoveInputKey(WPARAM inputKey); // キー入力解除
    void MemoryMouseMove(int xMove, int yMove); // マウス移動記録

    void ClearInputMemory(); // 入力クリア

    void SetCursorX(int x);
    void SetCursorY(int y);

    InputHandler();
    ~InputHandler();
};