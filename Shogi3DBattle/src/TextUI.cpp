#include"TextUI.h"

Text2D TextUI::GetText2D(){return _text2D;} // 2Dテキストを返す

TextUI::TextUI(Text2D text2D) : UI(text2D.rect), _text2D(text2D){}
