#pragma once

#include"I_Board.h"
#include"I_Piece.h"

class PiecePositionManager
{
private:
    std::vector<std::vector<I_Piece*>> _piecePosOnBoard; // 将棋盤上の駒の配置状況

    void ResizePiecePosOnBoardVec(unsigned int squareNum); // 将棋盤上の駒の配置状況のサイズを変更
    void InitPiecesPosBoard9x9(std::vector<I_Piece*> pieces); // 9x9将棋盤の初期位置へ駒を移動
    void MovePiecePos(I_Piece* piece, unsigned int row, unsigned int column); // 駒を指定のマスへ移動

public:
    void InitPiecesPos(std::vector<I_Piece*> pieces, I_Board* board); // 駒の位置を初期化
};