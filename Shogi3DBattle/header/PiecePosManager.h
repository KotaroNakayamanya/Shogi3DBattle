#pragma once

#include"I_Board.h"
#include"I_Piece.h"

class PiecePosManager
{
private:
    std::vector<std::vector<I_Piece*>> _placedPiece; // 将棋盤上の駒の位置を記憶する変数

    void ResizePlacedPieceVec(unsigned int squareNum); // 駒位置記録用の変数のサイズを変更
    void InitPiecesPosBoard9x9(std::vector<I_Piece*> pieces); // 9x9将棋盤の初期位置へ駒を移動
    void MovePiecePos(I_Piece* piece, unsigned int row, unsigned int column); // 駒を指定のマスへ移動

public:
    void InitPiecesPos(std::vector<I_Piece*> pieces, I_Board* board); // 駒の位置を初期化
    I_Piece* GetPlacedPiece(unsigned int row, unsigned int column); // マスに位置している駒を返す
};