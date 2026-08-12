#include"TextUI.h"

void   TextUI::SetText2D(Text2D text2D){_text2D = text2D;} // 2Dテキストセット
Text2D TextUI::GetText2D()             {return _text2D;}   // 2Dテキストを返す

TextUI::TextUI(Text2D text2D, bool active) : UI(text2D.rect), _text2D(text2D){}
