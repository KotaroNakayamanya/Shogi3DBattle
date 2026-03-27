#pragma once

#include"KeyMap.h"
#include<memory>

class ISceneState
{
public:
    // ÉVÅ[ÉììÆçÏ
    virtual ISceneState* ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) = 0;

    ISceneState()  = default;
    ~ISceneState(){}
};