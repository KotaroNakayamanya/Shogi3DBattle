#pragma once

#include<Windows.h>
#include<memory>
#include"IsceneState.h"
#include"KeyConf.h"

class InputHandler
{
private:
    std::unique_ptr<ISceneState> _sceneState; // シーンステート
    std::unique_ptr<KeyConf> _keyConf; // キーコンフィグ

    void CheckUpdateSceneState(ISceneState* sceneState); // シーンステート更新チェック
    void SetSceneState(ISceneState* sceneState); // シーンステート更新

public:
    void ExeLClick();    // 左クリック処理
    void ExeRClick();    // 右クリック処理
    void ExeMouseMove(); // マウス移動処理
    void ExeInputKey(WPARAM inputKey); // キー入力処理

    InputHandler();
    ~InputHandler();
};