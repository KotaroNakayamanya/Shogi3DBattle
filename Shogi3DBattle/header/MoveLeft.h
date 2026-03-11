#pragma once

#include"Move.h"
#include"Piece.h"

class MoveLeft : public Move
{
public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveLeft(Piece* piece);
    ~MoveLeft();
};