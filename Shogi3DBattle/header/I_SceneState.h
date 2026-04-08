#pragma once

#include"KeyMap.h"
#include<memory>

class I_SceneState
{
public:
    // ƒV[ƒ““®ì
    virtual std::unique_ptr<I_SceneState> ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) = 0;

    virtual ~I_SceneState() = default;
};