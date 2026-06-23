#pragma once

#include"I_Board.h"
#include"SideBoard.h"
#include"CubeVertIndices.h"
#include"I_Piece.h"
#include"PieceVertIndices.h"

class GameObjects
{
private:
    std::unique_ptr<I_Board>              _board;                // 将棋盤
    std::unique_ptr<SideBoard>            _sideBoard1;           // プレイヤー1の駒置き台
    std::unique_ptr<SideBoard>            _sideBoard2;           // プレイヤー2の駒置き台
    std::vector<std::unique_ptr<I_Piece>> _pieces;               // 駒

    std::unique_ptr<CubeVertIndices>      _cubeVertIndices; // 箱型の頂点インデックス
    std::unique_ptr<PieceVertIndices>     _pieceVertIndices;     // 駒の頂点インデックス

    void CreateBoard();       // 将棋盤作成
    void CreateSideBoards();  // 駒置き台作成
    void CreatePieces();      // 駒作成
    void CreateVertIndices(); // 頂点インデックス作成

public:
    void CreateGameObjects(); // ゲームオブジェクト作成

    I_Board*                GetBoard();          // 将棋盤を返す
    std::vector<SideBoard*> GetSideBoards();     // 駒置き台を返す
    std::vector<I_Piece*>   GetPieces();         // 駒を返す
    std::vector<I_GameObj*> GetAllGameObjects(); // 全てのゲームオブジェクトを返す

    std::vector<NaturalBufferedData<unsigned short>*> GetAllVertIndices();   // 全ての頂点インデックスを返す
    CubeVertIndices*                                  GetBoardVertIndices(); // 将棋盤の頂点インデックスを返す
    PieceVertIndices*                                 GetPieceVertIndices(); // 駒の頂点インデックスを返す

};