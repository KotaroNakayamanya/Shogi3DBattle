#include"I_ButtonUI.h"

void                     I_ButtonUI::SetTextAndRects(std::vector<TextAndRect> tr){_textAndRects = tr;}   // テキスト及び描画範囲セット
std::vector<TextAndRect> I_ButtonUI::GetTextAndRects()                           {return _textAndRects;} // テキスト及び描画範囲を返す

void I_ButtonUI::SetIsSelected(bool select){_isSelected = select;} // 選択状態セット
bool I_ButtonUI::IsSelected   ()           {return _isSelected;  } // 選択状態を返す

I_ButtonUI::I_ButtonUI(D2D1_RECT_F rect, std::vector<TextAndRect> textAndRects)
    : UI(rect), _textAndRects(textAndRects), _isSelected(false){}