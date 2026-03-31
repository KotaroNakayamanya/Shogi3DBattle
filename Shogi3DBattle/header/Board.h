#pragma once

#include"ShogiObj.h"

class Board : public ShogiObj
{
private:
public:
    void ChangeBoardTo55(); // «Šû”Õ‚ğ5~5‚É•ÏX
    void ChangeBoardTo99(); // «Šû”Õ‚ğ9~9‚É•ÏX

    Board();
    ~Board();
};