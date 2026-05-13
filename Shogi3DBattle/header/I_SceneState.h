#pragma once

#include<memory>

class I_SceneState
{
public:
    // ƒV[ƒ““®ìˆ—
    virtual std::unique_ptr<I_SceneState> ExeSceneProcess(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) = 0;

    virtual ~I_SceneState() = default;
};