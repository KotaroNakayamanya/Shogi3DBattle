#pragma once

#include"IButtonUI.h"
#include"TextAndRectStruct.h"

class IButtonUIFactory
{
public:
    virtual std::unique_ptr<IButtonUI> CreateButtonUI( // É{É^ÉìUIçÏê¨
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects) = 0;

    virtual ~IButtonUIFactory() = default;
};