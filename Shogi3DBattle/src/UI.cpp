#include"UI.h"

void        UI::SetRect(D2D1_RECT_F rect){_rect = rect;} // UI”ÍˆÍƒZƒbƒg
D2D1_RECT_F UI::GetRect()                {return _rect;}  // UI”ÍˆÍ‚ð•Ô‚·

UI::UI(D2D1_RECT_F rect) : _rect(rect){}