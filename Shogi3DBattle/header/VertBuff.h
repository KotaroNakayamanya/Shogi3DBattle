#pragma once

#include"Buff.h"
#include<memory>
//#include"Board.h"
//#include"Piece.h"
#include"Vertices.h"


class VertBuff : public Buff
{
public:
    //// 頂点バッファに書き込み
    //HRESULT WriteToVertBuff(Board* board, std::vector<std::unique_ptr<Piece>>& pieces);
    HRESULT WriteToBuff(Vertices* vertices, UINT idx);

    VertBuff();
    ~VertBuff();
};