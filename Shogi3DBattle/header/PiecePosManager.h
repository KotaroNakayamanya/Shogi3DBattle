#pragma once

#include"I_Board.h"
#include"I_Piece.h"

class PiecePosManager
{
private:
    std::vector<std::vector<I_Piece*>> _piecePlacedOnBoard;      // 将棋盤上の駒の位置を記録する変数
    std::vector<std::vector<I_Piece*>> _piecePlacedOnSideBoard1; // プレイヤー1の駒置き台上の駒の位置を記録する変数
    std::vector<std::vector<I_Piece*>> _piecePlacedOnSideBoard2; // プレイヤー2の駒置き台上の駒の位置を記録する変数

    void ResizePlacedPieceVec(unsigned int squareNum); // 駒位置記録用の変数のサイズを変更
    void InitPiecesPosBoard9x9(); // 9x9将棋盤の初期位置へ駒を移動

    void DeletePiecePlaced(I_Piece* piece); // 駒の位置の記録を消去する
    void DeleteFromSideBoard(std::vector<std::vector<I_Piece*>>& piecePlacedOnSideBoard, I_Piece* piece); // 駒置き台から駒の記録を消去する

public:
    void InitPiecesPos(); // 駒の位置を初期化

    void PlacePieceOnBoard     (I_Piece* piece, unsigned int row, unsigned int column); // 駒を指定のマスへ移動
    void PlacePieceOnSideBoard(std::vector<std::vector<I_Piece*>>& piecePlacedOnSideBoard, I_Piece* piece); // 駒を駒置き台へ移動                                    // 駒をプレイヤー1の駒置き台へ移動

    I_Piece* GetPlacedPiece(unsigned int row, unsigned int column); // マスに位置している駒を返す

    PiecePosManager();
};