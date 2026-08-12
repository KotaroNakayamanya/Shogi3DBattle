#include"UI.h"

D2D1_RECT_F UI::GetRect() {return _rect;}  // UI”ÍˆÍ‚ğ•Ô‚·

void   UI::SetIsActive(bool active){_isActive = active;} // Šˆ«ó‘ÔƒZƒbƒg
bool   UI::GetIsActive()           {return _isActive;  } // Šˆ«ó‘Ô‚ğ•Ô‚·

UI::UI(D2D1_RECT_F rect, bool active) : _rect(rect), _isActive(active){}