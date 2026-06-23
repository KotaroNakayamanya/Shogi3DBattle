#include"GameObjects.h"
#include<functional>
#include"Board9x9.h"
#include"King.h"
#include"Rook.h"
#include"Bishop.h"
#include"Gold.h"
#include"Silver.h"
#include"Knight.h"
#include"Lance.h"
#include"Pawn.h"

// 将棋盤作成
void GameObjects::CreateBoard()
{
    _board = std::make_unique<Board9x9>();
}

// 駒置き台作成
void GameObjects::CreateSideBoards()
{
    _sideBoard1           = std::make_unique<SideBoard>();
    _sideBoard2           = std::make_unique<SideBoard>();
}

// 駒作成
void GameObjects::CreatePieces()
{
    std::function<void(PlayerSide)> createPlayerPieces = [this](PlayerSide playerSide)
    {
        for (int i = 0; i < 1; i++) _pieces.push_back(std::make_unique<King>  (playerSide)); // 王 作成
        for (int i = 0; i < 1; i++) _pieces.push_back(std::make_unique<Rook>  (playerSide)); // 飛 作成
        for (int i = 0; i < 1; i++) _pieces.push_back(std::make_unique<Bishop>(playerSide)); // 角 作成
        for (int i = 0; i < 2; i++) _pieces.push_back(std::make_unique<Gold>  (playerSide)); // 金 作成
        for (int i = 0; i < 2; i++) _pieces.push_back(std::make_unique<Silver>(playerSide)); // 銀 作成
        for (int i = 0; i < 2; i++) _pieces.push_back(std::make_unique<Knight>(playerSide)); // 桂 作成
        for (int i = 0; i < 2; i++) _pieces.push_back(std::make_unique<Lance> (playerSide)); // 香 作成
        for (int i = 0; i < 9; i++) _pieces.push_back(std::make_unique<Pawn>  (playerSide)); // 歩 作成 
    };

    createPlayerPieces(PlayerSide::PLAYER_1); // プレイヤー１の駒作成
    createPlayerPieces(PlayerSide::PLAYER_2); // プレイヤー２の駒作成
}

// 頂点インデックス作成
void GameObjects::CreateVertIndices()
{
    _cubeVertIndices  = std::make_unique<CubeVertIndices>();
    _pieceVertIndices = std::make_unique<PieceVertIndices>();
}



// ゲームオブジェクト作成
void GameObjects::CreateGameObjects()
{
    CreateBoard();
    CreateSideBoards();
    CreatePieces();

    CreateVertIndices();
}



// 将棋盤を返す
I_Board* GameObjects::GetBoard()
{
    return _board.get();
}

// 駒置き台を返す
std::vector<SideBoard*> GameObjects::GetSideBoards()
{

    std::vector<SideBoard*> sideBoards;

    sideBoards.push_back(_sideBoard1.get());
    sideBoards.push_back(_sideBoard2.get());

    return sideBoards;
}

// 駒を返す
std::vector<I_Piece*> GameObjects::GetPieces()
{
    std::vector<I_Piece*> pieces;

    for(auto& piece : _pieces) pieces.push_back(piece.get());

    return pieces;
}

// 全てのゲームオブジェクトを返す
std::vector<I_GameObj*> GameObjects::GetAllGameObjects()
{

    std::vector<I_GameObj*> allGameObjects;

    allGameObjects.push_back(GetBoard());
    for(auto& sideBoard : GetSideBoards()) allGameObjects.push_back(sideBoard);
    for(auto& piece     : GetPieces())     allGameObjects.push_back(piece);

    return allGameObjects;
}



// 箱型の頂点インデックスを返す
CubeVertIndices*  GameObjects::GetBoardVertIndices()
{
    return _cubeVertIndices.get();
} 

// 駒の頂点インデックスを返す
PieceVertIndices* GameObjects::GetPieceVertIndices()
{
    return _pieceVertIndices.get();
} 

// 全ての頂点インデックスを返す
std::vector<NaturalBufferedData<unsigned short>*> GameObjects::GetAllVertIndices()
{
    std::vector<NaturalBufferedData<unsigned short>*> allVertIndices;

    allVertIndices.push_back(GetBoardVertIndices());
    allVertIndices.push_back(GetPieceVertIndices());

    return allVertIndices;
}
