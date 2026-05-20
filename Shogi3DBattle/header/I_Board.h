#pragma once

#include"I_GameObj.h"

class I_Board : public I_GameObj
{
private:
    float _boardSize; // «Šû”Õ1•Ó‚Ì’·‚³

public:
    virtual unsigned int GetBoardSquareNum() = 0; // «Šû”Õ‚Ìƒ}ƒX”‚ğ•Ô‚·

    float GetBoardSize(); // «Šû”Õ1•Ó‚Ì’·‚³‚ğ•Ô‚·

    I_Board(GameObjType gameObjType, float size);
    virtual ~I_Board() = default;
};