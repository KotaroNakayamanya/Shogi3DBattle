#pragma once

#include"UI.h"
#include"Text2D.h"

class TextUI : public UI
{
private:
    Text2D _text2D; // 2Dテキスト

public:
    void   SetText2D(Text2D text2D); // 2Dテキストセット
    Text2D GetText2D();              // 2Dテキストを返す

    TextUI(Text2D text2D);
};