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
    static Move  GetMoveForPlayer(PlayerSide playerSide); // プレイヤーにとっての上下左右のプラスマイナス1を返す
    
public:
    static bool  GetIsRowAndColumnCorrect(unsigned char row, unsigned char column); // 対象の位置が将棋盤上にあるかどうか返す
    static std::vector<std::vector<bool>> GetCanPlaced(I_Piece* piece); // 駒が移動できる位置を行列で返す
    static bool GetCanThisPlacedPiece(I_Piece* piece, unsigned char row, unsigned char column); // その位置に駒を動かせるかどうか返す
    static bool GetIsChecked(PlayerSide playerSide); // プレイヤーが王手されているか確認
    static bool GetIsWinning(PlayerSide playerSide); // プレイヤーが勝利しているか確認
    static bool GetCanPromotion(I_Piece* piece, unsigned char row, unsigned char column); // 成りが可能かどうか確認する
    static bool GetIsForcedPromotion(I_Piece* piece, unsigned char row, unsigned char column); // 成りが強制かどうか確認する
    static bool GetCanMove(I_Piece* piece); // 駒を動かすことが出来るかどうか返す

    static unsigned int GetAttackedBits( // 指定の位置がプレイヤーにとってどのように攻撃されているかをビットで返す
        PlayerSide playerSide,
        unsigned char row,
        unsigned char column);
};