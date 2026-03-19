#pragma once

#include"ShogiObj.h"

class Piece : public ShogiObj
{
public:
    void MoveX(float x); // x軸方向に動くようにワールド行列を変換する
    void MoveY(float y); // y軸方向に動くようにワールド行列を変換する      

    Piece();
    ~Piece();
};