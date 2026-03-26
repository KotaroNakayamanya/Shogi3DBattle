#include"KeyMap.h"

// キーマップを登録
void KeyMap::RegisterKeyMap(UCHAR key, InputHandler::Button button)
{
    _keyMap[key] = button;
}

// 入力キーを操作ボタンに変更
UCHAR KeyMap::ConvertKeyToButton(WPARAM input)
{
    auto it = _keyMap.find(input); // 割り当てられた操作ボタンが存在するか確認

    if(it != _keyMap.end())   
        return it->second;

    return 0; // 見つからなければ0（未入力）を返す
}

KeyMap::KeyMap(){}
KeyMap::~KeyMap(){}