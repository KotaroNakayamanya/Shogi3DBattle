#pragma once

#include"InputHandler.h"
#include<windows.h>
#include<map>

class KeyMap
{
public:
    

private:
    std::map<WPARAM, UCHAR> _keyMap; // キーと操作ボタンの対応

public:
    void RegisterKeyMap(UCHAR key, InputHandler::Button button); // キーマップを登録
    UCHAR ConvertKeyToButton(WPARAM input);        // キーを割り当てられた操作ボタンに変更

    KeyMap();
    ~KeyMap();
};