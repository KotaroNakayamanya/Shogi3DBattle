#include"I_ButtonUI.h"

void                I_ButtonUI::SetText2Ds(std::vector<Text2D> tr){_text2Ds = tr;}   // 2Dテキストセット
std::vector<Text2D> I_ButtonUI::GetText2Ds()                      {return _text2Ds;} // 2Dテキストを返す

void I_ButtonUI::SetIsSelected(bool select){_isSelected = select;} // 選択状態セット
bool I_ButtonUI::IsSelected   ()           {return _isSelected;  } // 選択状態を返す

I_ButtonUI::I_ButtonUI(D2D1_RECT_F rect, std::vector<Text2D> text2Ds)
    : UI(rect), _text2Ds(text2Ds), _isSelected(false){}