#pragma once

#include"Move.h"
#include"Piece.h"

class MoveRight : public Move
{
public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveRight(Piece* piece);
    ~MoveRight();
};