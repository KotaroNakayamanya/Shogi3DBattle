#include"UIObj.h"

std::wstring  UIObj::GetText()  {return _text;}   // テキストを返す
UIObj::UIType UIObj::GetUIType(){return _uiType;} // UIタイプを返す

void        UIObj::SetRect(D2D1_RECT_F rect){_rect = rect;}        // テキスト範囲セット
D2D1_RECT_F UIObj::GetRect()                {return _rect;}        // テキスト範囲を返す
void        UIObj::SetIsSelected(bool state){_isSelected = state;} // 選択状態セット
bool        UIObj::IsSelected()             {return _isSelected;}  // 選択状態を返す