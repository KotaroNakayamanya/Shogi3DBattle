#pragma once

#include"I_BoardFactory.h"

class Board9x9Factory : public I_BoardFactory
{
public:
    std::unique_ptr<I_Board> CreateBoard() override; // 9x9«Šû”Õì¬
};