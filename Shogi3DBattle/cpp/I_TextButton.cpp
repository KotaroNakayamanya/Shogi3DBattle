#include"I_TextButton.h"
#include"Application.h"

// 選択状態に合わせた処理実行
void I_TextButton::ExeSelectedStateProcess()
{
    // 活性状態なら実行
    if (_isActive) {
        auto dx12 = Application::GetInstance().GetDX12();
        
        // 選択されていたら赤色に、されていなければ黒色に
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
}

void I_TextButton::SetIsActive(bool active){_isActive = active;} // 活性状態セット
bool I_TextButton::GetIsActive()           {return _isActive;  } // 活性状態を返す

void                 I_TextButton::SetTextUIs(std::vector<TextUI*> textUIs){_textUIs = textUIs;} // ボタンに関連しているテキストUIセット
std::vector<TextUI*> I_TextButton::GetTextUIs()                            {return _textUIs;}    // ボタンに関連しているテキストUIを返す

I_TextButton::I_TextButton(D2D1_RECT_F rect, std::vector<TextUI*> textUIs, bool active)
    : I_Button(rect), _textUIs(textUIs), _isActive(active){}