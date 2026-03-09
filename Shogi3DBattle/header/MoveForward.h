#pragma once

#include"ICommand.h"
#include"Piece.h"

class MoveForward : public ICommand
{
private:
    Piece* _piece;

public:
    void Exe() override;  // é¿çs
    void Undo() override; // é¿çséÊÇËè¡Çµ

    MoveForward();
    ~MoveForward();
};