#pragma once

#include"I_GameObj.h"

class I_Board : public I_GameObj
{
private:
    float _boardSize; // «Šû”Õ1•Ó‚Ì’·‚³

public:
    float GetBoardSize(); // «Šû”Õ1•Ó‚Ì’·‚³‚ğ•Ô‚·

    I_Board(float size);
    virtual ~I_Board() = default;
};