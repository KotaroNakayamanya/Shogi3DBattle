#pragma once

#include"GameObj.h"

class Board : public GameObj
{
private:
public:
    void ChangeBoardTo55(); // «Šû”Õ‚ğ5~5‚É•ÏX
    void ChangeBoardTo99(); // «Šû”Õ‚ğ9~9‚É•ÏX

    Board () = default;
    ~Board() = default;
};