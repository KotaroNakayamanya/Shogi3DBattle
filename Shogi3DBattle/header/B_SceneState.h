#pragma once

#include"I_SceneState.h"

class B_SceneState : public I_SceneState
{
public:
    // ƒV[ƒ““®ìˆ—
    virtual std::unique_ptr<I_SceneState> ExeSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) = 0;
};