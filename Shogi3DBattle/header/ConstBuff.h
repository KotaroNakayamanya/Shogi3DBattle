#pragma once

#include<Buff.h>
#include<memory>
#include"Board.h"
#include"Piece.h"
#include"Camera.h"

class ConstBuff : public Buff
{
public:
    // •ÏŠ·s—ñ‚ğ‘‚«‚Ş
    void WriteToConstBuff(
        Board* board,
        std::vector<std::unique_ptr<Piece>>& pieces,
        Camera* camera);

    ConstBuff()  = default;
    ~ConstBuff() = default;
};