#include"I_Button.h"
#include"Application.h"

void I_Button::SetIsSelected(bool select){_isSelected = select;} // 選択状態セット
bool I_Button::IsSelected   ()           {return _isSelected;  } // 選択状態を返す

I_Button::I_Button(D2D1_RECT_F rect) : UI(rect), _isSelected(false){}