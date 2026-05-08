#include"I_TextButton.h"
#include"Application.h"

// 選択状態に合わせた処理実行
void I_TextButton::ExeSelectedStateProcess()
{
    auto dx12 = Application::GetInstance().GetDX12();
    
    ID2D1SolidColorBrush* brush;
    if(IsSelected()) brush = dx12->GetRedBrush();
    else             brush = dx12->GetBlackBrush();

    for (auto textUI : _textUIs)
    {
        auto text2D = textUI->GetText2D();
        text2D.brush = brush;
        textUI->SetText2D(text2D);
    }
}

void                 I_TextButton::SetTextUIs(std::vector<TextUI*> textUIs){_textUIs = textUIs;} // ボタンに関連しているテキストUIセット
std::vector<TextUI*> I_TextButton::GetTextUIs()                            {return _textUIs;}    // ボタンに関連しているテキストUIを返す

I_TextButton::I_TextButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs)
    : I_Button(rect), _textUIs(textUIs){}