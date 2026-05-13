#include"PiecePosManager.h"
#include<cassert>
#include<functional>

// 駒の位置を初期化
void PiecePosManager::InitPiecesPos(std::vector<I_Piece*> pieces, I_Board* board)
{
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_99:
            ResizePlacedPieceVec(9);
            InitPiecesPosBoard9x9(pieces);
            break;

        default:
            assert(false);
            return;
    }
}
// 駒位置記録用の変数のサイズを変更
void PiecePosManager::ResizePlacedPieceVec(unsigned int squareNum)
{
    _placedPiece.clear();
    _placedPiece.resize(squareNum);
    for(auto& piecePosOnRow : _placedPiece) piecePosOnRow.resize(squareNum);
}




// 9x9将棋盤の初期位置へ駒を移動
void PiecePosManager::InitPiecesPosBoard9x9(std::vector<I_Piece*> pieces)
{
    for (auto piece : pieces)
    {
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
            if (_placedPiece[row-1][column-1] == nullptr) // 配置を試みる
            {
                PlacePiece(piece, row, column);
                isSet = true;
            }
            else if (_placedPiece[row-1][9 - column] == nullptr) // 既に配置されていたら、反対側の列に配置を試みる
            {
                PlacePiece(piece, row, 10-column);
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
void PiecePosManager::PlacePiece(I_Piece* piece, unsigned int row, unsigned int column)
{
    // 駒が位置していたマスを空にし、新しい場所に位置させる
    for(auto& placedPiecesInRow : _placedPiece)
        for(auto& placedPiece : placedPiecesInRow) 
            if(placedPiece == piece)
                placedPiece = nullptr;
    _placedPiece[row-1][column-1] = piece;

    auto worldMat = DirectX::XMMatrixIdentity();

    if(piece->GetPlayerSide() == PlayerSide::PLAYER_1) // 自身の駒なら向きを変更
        worldMat *= DirectX::XMMatrixRotationZ(DirectX::XM_PI);

    auto xPos = 10.0f * column;
    auto yPos = 10.0f * row;
    worldMat *= DirectX::XMMatrixTranslation(xPos, yPos, 0.0f);

    auto worldMatObj = piece->GetWorldMat();
    worldMatObj->SetMat(worldMat);
}

// マスに位置している駒を返す
I_Piece* PiecePosManager::GetPlacedPiece(unsigned int row, unsigned int column)
{
    return _placedPiece[row-1][column-1];
}