#include"RuleManager.h"
#include"Application.h"
#include"PieceMovementBit.h"

// 対象の位置が将棋盤上にあるかどうか返す
bool RuleManager::GetIsRowAndColumnCorrect(unsigned char row, unsigned char column)
{
    auto board = Application::GetInstance().GetGameObjects()->GetBoard();

    auto isRowCorrect    = false;
    auto isColumnCorrect = false;
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_99:
            isRowCorrect    = (1<=row   ) && (row   <=9);
            isColumnCorrect = (1<=column) && (column<=9);
            break;

        default:
            break;
    }

    return isRowCorrect && isColumnCorrect;
}

// プレイヤーにとっての上下左右のプラスマイナス1を返す
RuleManager::Move RuleManager::GetMoveForPlayer(PlayerSide playerSide)
{
    Move move;
    
    switch (playerSide)
    {
        // プレイヤー1は右上がマイナス
        case PlayerSide::PLAYER_1:
            move.right = -1;
            move.up    = -1;
            move.left  =  1;
            move.down  =  1;
            break;

        // プレイヤー2は右上がプラス
        case PlayerSide::PLAYER_2:
            move.right =  1;
            move.up    =  1;
            move.left  = -1;
            move.down  = -1;
            break;

        default:
            break;
    }

    return move;
}



// 駒が移動できる位置を行列で返す
std::vector<std::vector<bool>> RuleManager::GetCanPlaced(I_Piece* piece)
{
    // 空の行列を作る
    std::vector<std::vector<bool>> canPlaced;

    // 将棋盤のサイズに合わせる
    unsigned char rowSquareNum;
    auto board = Application::GetInstance().GetGameObjects()->GetBoard();
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_99:
            rowSquareNum = 9;
            canPlaced.resize(rowSquareNum);
            for(auto& column : canPlaced) column.resize(rowSquareNum);
            break;

        default:
            break;
    }

    // 一旦、全てfalseを入れる
    for (auto& column : canPlaced)
    {
        for(auto square : column) square = false;
    }
   
    // 駒がどこにいるのか探す
    auto& app             = Application::GetInstance();
    auto  piecePosManager = app.GetPiecePosManager();
    unsigned char placedRow;
    unsigned char placedColumn;
    bool          isFound = false;
    for (unsigned int i = 1; i <= rowSquareNum; i++)
    {
        for (unsigned int j = 1; j <= rowSquareNum; j++)
        {
            // 駒を走査する　nullではなく、対象の駒であれば位置を記録して処理を抜ける
            auto targetPiece = piecePosManager->GetPlacedPiece(i, j);
            if(targetPiece == nullptr) continue;
            if (targetPiece == piece)
            {
                placedRow    = i;
                placedColumn = j;
                isFound      = true;
                break;
            }
        }

        // 見つかったら処理を抜ける
        if(isFound) break;
    }

    // 以下、動ける範囲をtrueにする
    // 駒の移動可能ビットを取得
    auto movementBits = piece->GetMovementBits();

    // 将棋盤上で見つかった場合は現在の位置から動ける範囲をtrueにする
    if (isFound)
    {
        unsigned char tempRow;
        unsigned char tempColumn;

        // プレイヤーにとっての上下左右のプラスマイナスを取得
        auto move = GetMoveForPlayer(piece->GetPlayerSide());

        // 下に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }

        // 左に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetLeftBit()) > 0)
        {
            tempRow    = placedRow;
            tempColumn = placedColumn + move.left;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 右に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetRightBit()) > 0)
        {
            tempRow    = placedRow;
            tempColumn = placedColumn + move.right;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 上に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 左下に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetLeftDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn + move.left;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 右下に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetRightDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn + move.right;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 左上に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetLeftUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn + move.left;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 右上に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetRightUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn + move.right;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 左上上に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetLeftDoubleUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up*2;
            tempColumn = placedColumn + move.left;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 右上上に移動可能かどうか確認
        if ((movementBits & PieceMovementBit::GetRightDoubleUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up*2;
            tempColumn = placedColumn + move.right;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにする
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }
            }
        }
        // 下直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow += move.down;
            }
        }
        // 左直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightLeftBit()) > 0)
        {
            tempRow    = placedRow;
            tempColumn = placedColumn + move.left;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempColumn += move.left;
            }
        }
        // 右直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightRightBit()) > 0)
        {
            tempRow    = placedRow;
            tempColumn = placedColumn + move.right;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempColumn += move.right;
            }
        }
        // 上直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow += move.up;
            }
        }
        // 左下直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightLeftDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn + move.left;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow    += move.down;
                tempColumn += move.left;
            }
        }
        // 右下直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightRightDownBit()) > 0)
        {
            tempRow    = placedRow    + move.down;
            tempColumn = placedColumn + move.right;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow    += move.down;
                tempColumn += move.right;
            }
        }
        // 左上直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightLeftUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn + move.left;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow    += move.up;
                tempColumn += move.left;
            }
        }
        // 右上直進が可能かどうか確認
        if ((movementBits & PieceMovementBit::GetStraightRightUpBit()) > 0)
        {
            tempRow    = placedRow    + move.up;
            tempColumn = placedColumn + move.right;
            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分の駒であればtrueにし、処理を抜ける
                {
                    if (targetPiece->GetPlayerSide() != piece->GetPlayerSide())
                    {
                        canPlaced[tempRow - 1][tempColumn - 1] = true;
                    }
                    break;
                } 
                else // 駒がいなければ移動可能につき、trueにする
                {
                    canPlaced[tempRow - 1][tempColumn - 1] = true;
                }

                // 次を走査する
                tempRow    += move.up;
                tempColumn += move.right;
            }
        }
    }
    else // 将棋盤上にいなければ駒がいない範囲を基本、trueとする
    {

    }

    return canPlaced;
}

// その位置に駒を動かせるかどうか返す
bool RuleManager::GetCanThisPlacedPiece(I_Piece* piece, unsigned char row, unsigned char column)
{
    // 行と列が正当かどうか確認し、正当でなければfalseを返す
    auto isRowAndColumnCorrect = GetIsRowAndColumnCorrect(row, column);
    if(!isRowAndColumnCorrect) return false;

    // その駒が移動できる範囲を取得し、対象の位置の真偽を返す
    auto canPlaced = GetCanPlaced(piece);
    return canPlaced[row - 1][column - 1];
}

// プレイヤーが勝利しているか確認
bool RuleManager::IsWinning(PlayerSide playerSide)
{
    auto& app = Application::GetInstance();
    auto piecePosManager = app.GetPiecePosManager();


    // 相手玉を探す
    PlayerSide    opponentPlayerSide;
    unsigned char opponentKingRow    = 0;
    unsigned char opponentKingColumn = 0;
    for (int i = 1; i <= 9; i++)
    {
        bool isFound = false;

        for (int j = 1; j <= 9; j++)
        {
            auto piece = piecePosManager->GetPlacedPiece(i, j);

            if(piece == nullptr)                             continue; // 何もいなければ次へ
            if(piece->GetGameObjType() != GameObjType::KING) continue; // 王でなければ次へ
            opponentPlayerSide = piece->GetPlayerSide();
            if(opponentPlayerSide == playerSide)             continue; // 自分側の駒であれば次へ

            // 相手の王の位置を記録
            opponentKingRow    = i;
            opponentKingColumn = j;
            isFound            = true;
            break;
        }

        if(isFound) break;
    }
    
    //
    // 実験　相手の王を攻撃されていたら勝利とする
    // 
    // 攻撃されているかどうかを返す
    auto attackedBits = GetAttackedBits(opponentPlayerSide, opponentKingRow, opponentKingColumn);

    return attackedBits > 0 ? true : false;
}

// 指定の位置がプレイヤーにとってどのように攻撃されているかをビットで返す場所か返す
unsigned int RuleManager::GetAttackedBits( 
    PlayerSide playerSide,
    unsigned char row,
    unsigned char column)
{
    // プレイヤーにとっての上下左右のプラスマイナスを取得する
    auto move = GetMoveForPlayer(playerSide);

    // 駒が可能な動きであればtrueを返す関数
    auto IsPossibleMovement = [](I_Piece* piece, unsigned short movementBit)
    {
        auto pieceMovement = piece->GetMovementBits();
        auto andBit = pieceMovement & movementBit;
        
        return andBit > 0 ? true : false;
    };

    // 以下、様々な方向から攻撃されているかチェック
    unsigned int attackedBits = 0;
    auto tempRow    = 0;
    auto tempColumn = 0;
    auto piecePosManager = Application::GetInstance().GetPiecePosManager();


    // 下から攻撃されているか確認
    tempRow    = row    + move.down;
    tempColumn = column;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、下への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 左から攻撃されているか確認
    tempRow    = row;
    tempColumn = column + move.left;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetLeftBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 右から攻撃されているか確認
    tempRow    = row;
    tempColumn = column + move.right;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetRightBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 上から攻撃されているか確認
    tempRow    = row    + move.up;
    tempColumn = column;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、上への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 左下から攻撃されているか確認
    tempRow    = row    + move.down;
    tempColumn = column + move.left;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左下への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetLeftDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 右下から攻撃されているか確認
    tempRow    = row    + move.down;
    tempColumn = column + move.right;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右下への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetRightDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }


    // 左上から攻撃されているか確認
    tempRow    = row    + move.up;
    tempColumn = column + move.left;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左上への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetLeftUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }


    // 右上から攻撃されているか確認
    tempRow    = row    + move.up;
    tempColumn = column + move.right;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右上への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetRightUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 左上上から攻撃されているか確認
    tempRow    = row    + move.up*2;
    tempColumn = column + move.left;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左上上への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetLeftDoubleUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 右上上から攻撃されているか確認 
    tempRow    = row    + move.up*2;
    tempColumn = column + move.right;
    if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右上上への移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetRightDoubleUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;;
        }
    }

    // 下から直進攻撃をされているか確認
    tempRow    = row    + move.down;
    tempColumn = column;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、下直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow += move.down;
    }

    // 左から直進攻撃をされているか確認
    tempRow    = row;
    tempColumn = column + move.left;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightLeftBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempColumn += move.left;
    }

    // 右から直進攻撃をされているか確認
    tempRow    = row;
    tempColumn = column + move.right;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightRightBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempColumn += move.right;
    }

    // 上から直進攻撃をされているか確認
    tempRow    = row    + move.up;
    tempColumn = column;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、上直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow += move.up;
    }

    return attackedBits;
}