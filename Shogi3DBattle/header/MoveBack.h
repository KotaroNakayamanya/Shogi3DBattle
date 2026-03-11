#pragma once

#include"Move.h"
#include"Piece.h"

class MoveBack : public Move
{
public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveBack(Piece* piece);
    ~MoveBack();
};