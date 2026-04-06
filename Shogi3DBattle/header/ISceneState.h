#pragma once

#include"KeyMap.h"
#include<memory>

class ISceneState
{
public:
    // ÉVÅ[ÉììÆçÏ
    virtual std::unique_ptr<ISceneState> ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) = 0;

    virtual ~ISceneState() = default;
};