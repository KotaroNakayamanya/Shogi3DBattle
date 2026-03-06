#pragma once

#include<Windows.h>
#include<map>
#include"InputCommand.h"

class KeyMap
{
private:
    // キーと操作ボタンの対応
    std::map<WPARAM, InputCommand> keyMap
    {
        {'w', InputCommand::up},
        {'a', InputCommand::left},
        {'s', InputCommand::down},
        {'d', InputCommand::right}
    };

public:
    // キーを割り当てた方向操作に変更
    InputCommand convertKeyToDirection(WPARAM input);

    KeyMap();
    ~KeyMap();
};