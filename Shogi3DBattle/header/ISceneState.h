#pragma once

#include"KeyMap.h"
#include<memory>

class ISceneState
{
public:
    // ‘€ìŠJn
    virtual ISceneState* ExeOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) = 0;

    ISceneState()  = default;
    ~ISceneState(){}
};