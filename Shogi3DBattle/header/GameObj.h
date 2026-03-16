#pragma once

#include<memory>
#include"Board.h"
#include"Pawn.h"

class GameObj
{
private:
    std::unique_ptr<Board> _board; // «Šû”Õ
    std::unique_ptr<Pawn>  _pawn;  // •à

    void CreateBoard();
    void CreatePawn();

public:
    void InitGameObj();

    Board* GetBoard(); // «Šû”Õ‚ğ•Ô‚·
    Pawn*  GetPawn();  // •à‚ğ•Ô‚·

    GameObj();
    ~GameObj();
};