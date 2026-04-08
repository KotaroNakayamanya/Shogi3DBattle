#pragma once

#include"I_ButtonUI.h"
#include"TextAndRectStruct.h"

class I_ButtonUIFactory
{
public:
    virtual std::unique_ptr<I_ButtonUI> CreateButtonUI( // É{É^ÉìUIçÏê¨
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) = 0;

    virtual ~I_ButtonUIFactory() = default;
};