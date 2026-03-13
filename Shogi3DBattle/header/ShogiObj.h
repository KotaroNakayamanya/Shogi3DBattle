#pragma once

#include"Board.h"
#include"Piece.h"
#include<memory>
#include<vector>

class ShogiObj
{
    friend class Application; // アプリケーションから参照可能

private:
    std::unique_ptr<Board> _board;
    std::vector<std::unique_ptr<Piece>> _pieces;

public:
    ShogiObj();
    ~ShogiObj();
};