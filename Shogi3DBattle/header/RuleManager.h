#pragma once

#include"PlayerSide.h"
#include"I_Piece.h"

class RuleManager
{
public:
    struct Move
    {
        char up;
        char down;
        char left;
        char right;
    };

private:
    static Move GetMoveForPlayer(PlayerSide playerSide); // プレイヤーにとっての上下左右のプラスマイナス1を返す
    static bool GetIsRowAndColumnCorrect(unsigned char row, unsigned char column); // 対象の位置が将棋盤上にあるかどうか返す
    
public:
    static std::vector<std::vector<bool>> GetCanPlaced(I_Piece* piece); // 駒が移動できる位置を行列で返す
    static bool GetCanThisPlacedPiece(I_Piece* piece, unsigned char row, unsigned char column); // その位置に駒を動かせるかどうか返す

    static bool IsWinning(PlayerSide playerSide); // プレイヤーが勝利しているか確認

    static unsigned int GetAttackedBits( // 指定の位置がプレイヤーにとってどのように攻撃されているかをビットで返す
        PlayerSide playerSide,
        unsigned char row,
        unsigned char column);
};