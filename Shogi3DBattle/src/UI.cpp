#include"UI.h"

std::wstring UI::GetText()  {return _text;}   // テキストを返す
UIType       UI::GetUIType(){return _uiType;} // UIタイプを返す

void        UI::SetRect(D2D1_RECT_F rect){_rect = rect;}        // テキスト範囲セット
D2D1_RECT_F UI::GetRect()                {return _rect;}        // テキスト範囲を返す
void        UI::SetIsSelected(bool state){_isSelected = state;} // 選択状態セット
bool        UI::IsSelected()             {return _isSelected;}  // 選択状態を返す