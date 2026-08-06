#pragma once

#include"PlayerSide.h"

class RuleManager
{
private:
    
public:
    static bool IsWinning(PlayerSide playerSide); // プレイヤーが勝利しているか確認

    static unsigned int GetAttackedBits( // 指定の位置がプレイヤーにとってどのように攻撃されているかをビットで返す
        PlayerSide playerSide,
        unsigned char row,
        unsigned char column);
};