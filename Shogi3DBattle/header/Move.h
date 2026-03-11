#pragma once

#include"ICommand.h"
#include"Piece.h"

class Move : public ICommand
{
protected:
    Piece* _piece;

    Move(Piece* piece) : _piece(piece){}
    ~Move(){}
};