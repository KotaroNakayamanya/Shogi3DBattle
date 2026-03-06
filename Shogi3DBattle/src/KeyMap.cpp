#include"KeyMap.h"

// キーを操作ボタンに変更
InputCommand KeyMap::convertKeyToDirection(WPARAM input)
{
    auto it = keyMap.find(input);

    if(it != keyMap.end())   
        return it->second;

    return InputCommand::none; // 見つからなければ未定義を返す
}

KeyMap::KeyMap(){}
KeyMap::~KeyMap(){}