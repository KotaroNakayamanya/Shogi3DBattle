#pragma once

#include<Windows.h>
#include<map>
#include"ControllerButton.h"

class KeyConf
{
private:
    // キーと操作ボタンの対応
    std::map<WPARAM, unsigned char> _keyConf
    {
        {'w', ControllerButton::up},
        {'a', ControllerButton::left},
        {'s', ControllerButton::down},
        {'d', ControllerButton::right}
    };

public:
    // キーを割り当てられた操作ボタンに変更
    unsigned char convertKeyToControllerButton(WPARAM input);

    KeyConf();
    ~KeyConf();
};