#pragma once

#include"B_BoardFactory.h"

class Board9x9Factory : public B_BoardFactory
{
public:
    std::unique_ptr<I_Board> CreateBoard() override; // 9x9«Šû”Õì¬
};