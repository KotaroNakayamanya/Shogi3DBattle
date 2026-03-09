#include"KeyConf.h"

// 入力キーを操作ボタンに変更
ControllerButton KeyConf::convertKeyToControllerButton(WPARAM input)
{
    auto it = _keyConf.find(input); // 割り当てられた操作ボタンが存在するか確認

    if(it != _keyConf.end())   
        return it->second;

    return ControllerButton::none; // 見つからなければ未定義を返す
}

KeyConf::KeyConf(){}
KeyConf::~KeyConf(){}