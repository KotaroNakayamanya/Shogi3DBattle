#include"PiecePosManager.h"
#include"Application.h"
#include<cassert>
#include<functional>
#include"VecCalc.h"

// 駒の位置を初期化
void PiecePosManager::InitPiecesPos()
{
    auto& app = Application::GetInstance();

    // 駒を初期化
    auto pieces = app.GetGameObjects()->GetPieces();
    auto piecenum = static_cast<unsigned int>(pieces.size());
    for (unsigned int i = 0; i < piecenum; i++)
    {
        // 駒を半分にプレイヤーを分ける
        auto playerside = i < (piecenum/2) ?
            PlayerSide::PLAYER_1 : PlayerSide::PLAYER_2;
        pieces[i]->SetPlayerSide(playerside);
    }
    
    // 将棋盤取得
    auto board = app.GetGameObjects()->GetBoard();

    // 将棋盤のサイズに応じて記録用サイズを決定
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_99:
            ResizePlacedPieceVec(9);
            InitPiecesPosBoard9x9();
            break;

        default:
            assert(false);
            return;
    }
}

// 王の位置を返す
PiecePosManager::Place PiecePosManager::GetKingPlace(PlayerSide playerSide)
{
    // 行の数を取得する
    unsigned char rowSquareNum = _piecePlacedOnBoard.size();

    // 王を探す
    Place place;
    for (int i = 1; i <= rowSquareNum; i++)
    {
        bool isFound = false;

        for (int j = 1; j <= rowSquareNum; j++)
        {
            auto piece = GetPlacedPiece(i, j);

            if(piece == nullptr)                             continue; // 何もいなければ次へ
            if(piece->GetGameObjType() != GameObjType::KING) continue; // 王でなければ次へ
            if(piece->GetPlayerSide()  != playerSide)        continue; // 自分側の駒でなければ次へ

            // 王の位置を記録
            place.row    = i;
            place.column = j;
            isFound            = true;
            break;
        }

        if(isFound) break;
    }

    return place;
}

// 駒位置記録用の変数のサイズを変更
void PiecePosManager::ResizePlacedPieceVec(unsigned int squareNum)
{
    _piecePlacedOnBoard.clear();
    _piecePlacedOnBoard.resize(squareNum);
    for(auto& piecePosOnRow : _piecePlacedOnBoard) piecePosOnRow.resize(squareNum);
}




// 駒の位置の記録を消去する
void PiecePosManager::DeletePiecePlaced(I_Piece* piece)
{
    // 将棋盤上から消去
    for(auto& placedPiecesInRow : _piecePlacedOnBoard)
        for(auto& placedPiece : placedPiecesInRow) 
            if(placedPiece == piece)
                placedPiece = nullptr;

    // 駒置き台上から消去
    DeleteFromSideBoard(_piecePlacedOnSideBoard1, piece);
    DeleteFromSideBoard(_piecePlacedOnSideBoard2, piece);
}

// 駒置き台を返す
std::vector<std::vector<I_Piece*>> PiecePosManager::GetPiecePlacedOnSideBoard(PlayerSide playerSide)
{
    switch (playerSide)
    {
        case PlayerSide::PLAYER_1:
            return _piecePlacedOnSideBoard1;
            break;

        case PlayerSide::PLAYER_2:
            return _piecePlacedOnSideBoard2;
            break;

        default:
            break;
    }
}

// 駒置き台から駒の記録を消去する
void PiecePosManager::DeleteFromSideBoard(std::vector<std::vector<I_Piece*>>& piecePlacedOnSideBoard, I_Piece* piece)
{
    for(auto& placedPieces : piecePlacedOnSideBoard)
        for (unsigned int i = 0; i < static_cast<unsigned int>(placedPieces.size()); i++)
        {
            if (placedPieces[i] == piece)
            {
                placedPieces.erase(placedPieces.begin() + i);
                break;
            }
        }
}



// 9x9将棋盤の初期位置へ駒を移動
void PiecePosManager::InitPiecesPosBoard9x9()
{
    // 駒取得
    auto pieces = Application::GetInstance().GetGameObjects()->GetPieces();

    for (auto piece : pieces)
    {
        // 駒を成っていない状態にする
        piece->SetIsPromotion(false);

        // 中央（5五...vectorでは[4][4]）からずらして配置させる
        int rowOffset, columnOffset;
        switch (piece->GetGameObjType())
        {
            case GameObjType::KING:
                rowOffset    =  4;
                columnOffset =  0;
                break;

            case GameObjType::ROOK:
                rowOffset    =  3;
                columnOffset = -3;
                break;

            case GameObjType::BISHOP:
                rowOffset    =  3;
                columnOffset =  3;
                break;

            case GameObjType::GOLD:
                rowOffset    =  4;
                columnOffset =  1;
                break;

            case GameObjType::SILVER:
                rowOffset    =  4;
                columnOffset =  2;
                break;
                
            case GameObjType::KNIGHT:
                rowOffset    =  4;
                columnOffset =  3;
                break;

            case GameObjType::LANCE:
                rowOffset    =  4;
                columnOffset =  4;
                break;

            case GameObjType::PAWN:
                rowOffset    =  2;
                columnOffset =  0;
                break;

            default:
                assert(false);
                return;
        }

        if (piece->GetPlayerSide() == PlayerSide::PLAYER_2) // 相手側の駒なら符号を逆にする
        {
            rowOffset    = -rowOffset;
            columnOffset = -columnOffset;
        }

        // 中央からオフセットを足して配置場所を得る
        auto row    = 5 + rowOffset;
        auto column = 5 + columnOffset;

        auto isSet = false;
        while (!isSet)
        {
            if (_piecePlacedOnBoard[row-1][column-1] == nullptr) // 配置を試みる
            {
                PlacePieceOnBoard(piece, row, column);
                isSet = true;
            }
            else if (_piecePlacedOnBoard[row-1][9 - column] == nullptr) // 既に配置されていたら、反対側の列に配置を試みる
            {
                PlacePieceOnBoard(piece, row, 10-column);
                isSet = true;
            }
            else // 反対側の列もすでに配置されているなら、配置場所の列を外側に1つ分ずらしてループに戻る
            {
                if(column <= 4) column--;
                else            column++;
            }
        }
    }
}

// 駒を指定のマスへ移動
void PiecePosManager::PlacePieceOnBoard(I_Piece* piece, unsigned int row, unsigned int column)
{
    // 元の駒の場所を削除
    DeletePiecePlaced(piece);

    auto elementRow    = row    - 1;
    auto elementColumn = column - 1;
    // 移動させる位置に駒が存在したら、その駒を駒置き台に移動する
    auto& targetSquarePiece = _piecePlacedOnBoard[elementRow][elementColumn];
    if (targetSquarePiece != nullptr)
    {
        // ターゲットの駒を取る側の駒の色にする
        auto player = piece->GetPlayerSide();
        targetSquarePiece->SetPlayerSide(player);

        // 取る側の駒置き台に移動させる
        auto& sideBoard = player == PlayerSide::PLAYER_1 ?
            _piecePlacedOnSideBoard1 : _piecePlacedOnSideBoard2;
        PlacePieceOnSideBoard(sideBoard, targetSquarePiece);
    }

    // 新しい場所に記録させる
    targetSquarePiece = piece;

    // ワールド行列等修正
    auto worldMat = DirectX::XMMatrixIdentity();

    // プレイヤー１の駒なら向きを変更
    if(piece->GetPlayerSide() == PlayerSide::PLAYER_1) 
        worldMat *= DirectX::XMMatrixRotationZ(DirectX::XM_PI);

    // 駒の厚みの半分だけずらし、成っているなら裏返す
    float halfThickness = piece->GetHalfThickness();
    worldMat *= DirectX::XMMatrixTranslation(0.0f, 0.0f, halfThickness);
    if(piece->GetIsPromotion())
        worldMat *= DirectX::XMMatrixRotationY(DirectX::XM_PI);

    // 指定のマスの位置に平行移動する
    auto xPos = 10.0f * column;
    auto yPos = 10.0f * row;
    worldMat *= DirectX::XMMatrixTranslation(xPos, yPos, -halfThickness);

    // ワールド行列を格納する
    auto worldMatObj = piece->GetWorldMat();
    worldMatObj->SetMat(worldMat);


}

// 駒を駒置き台へ移動
void PiecePosManager::PlacePieceOnSideBoard(std::vector<std::vector<I_Piece*>>& piecePlacedOnSideBoard, I_Piece* piece)
{
    // 元の駒の場所を削除
    DeletePiecePlaced(piece);

    // 駒を成っていない状態にする
    piece->SetIsPromotion(false);

    // 駒置き台に記録する
    unsigned char insertEle;
    auto gameObjType = piece->GetGameObjType();
    for (unsigned int i = 0; i < static_cast<unsigned int>(piecePlacedOnSideBoard.size()); i++)
    {
        auto& placedPieces = piecePlacedOnSideBoard[i];

        // 駒置き台の、空いている場所か、既に同種類の駒が置かれている場所に記録
        auto isEmpty = placedPieces.size() == 0;
        auto isExist = isEmpty ? 
            false : placedPieces[0]->GetGameObjType() == gameObjType;

        if (isEmpty || isExist)
        {
            placedPieces.push_back(piece);
            insertEle = i;
            break;
        }

    }
    
    // ワールド行列等修正
    auto playerSide = piece->GetPlayerSide();

    auto baseX   = playerSide == PlayerSide::PLAYER_1 ?
        -5.0f : 105.0f;
    auto baseY   = playerSide == PlayerSide::PLAYER_1 ?
        75.0f : 25.0f; 
    auto offsetX = playerSide == PlayerSide::PLAYER_1 ?
        -10.0f : 10.0f;
    auto offsetY = playerSide == PlayerSide::PLAYER_1 ?
        10.0f : -10.0f;

    auto xPos = baseX + offsetX*(insertEle%3);
    auto yPos = baseY + offsetY*(insertEle/3);
    auto newWorldMat = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

    // プレイヤー1側の駒なら回転する
    if(playerSide == PlayerSide::PLAYER_1) newWorldMat *= DirectX::XMMatrixRotationZ(DirectX::XM_PI);


    // 平行移動し、ワールド行列としてセットする
    newWorldMat *= DirectX::XMMatrixTranslation(xPos, yPos, 0.0f);
    piece->GetWorldMat()->SetMat(newWorldMat);
}

// 将棋盤上に指定の駒が存在するか確認する
bool PiecePosManager::GetIsPiecePlacedOnBoard(I_Piece* piece)
{
    for (auto& column : _piecePlacedOnBoard)
    {
        for (auto& square : column)
        {
            if(square == piece) return true;
        }
    }

    return false;
}

// マスに位置している駒を返す
I_Piece* PiecePosManager::GetPlacedPiece(unsigned int row, unsigned int column)
{
    return _piecePlacedOnBoard[row-1][column-1];
}

PiecePosManager::PiecePosManager()
{
    _piecePlacedOnSideBoard1.resize(7);
    _piecePlacedOnSideBoard2.resize(7);
}