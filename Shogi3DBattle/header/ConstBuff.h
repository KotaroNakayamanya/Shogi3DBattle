#pragma once

#include<Buff.h>
#include<memory>
#include<array>
#include"Board.h"
#include"Piece.h"
#include"ViewMat.h"
#include"ProjMat.h"

class ConstBuff : public Buff
{
public:
    // •ÏŠ·s—ñ‚ğ‘‚«‚Ş
    void WriteToConstBuff(
        Board* board,
        std::array<std::unique_ptr<Piece>, 40>& pieces,
        ViewMat* viewMat,
        ProjMat* projMat);

    ConstBuff();
    ~ConstBuff();
};