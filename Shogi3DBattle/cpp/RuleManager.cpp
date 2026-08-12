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
    auto playerSide = piece->GetPlayerSide();
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
    auto movementBits = piece->GetMovementBits();

    // プレイヤーにとっての上下左右のプラスマイナスを取得
    auto move = GetMoveForPlayer(piece->GetPlayerSide());

    // 将棋盤上で見つかった場合は、現在の位置から動ける範囲をtrueにする
    if (isFound)
    {
        unsigned char tempRow;
        unsigned char tempColumn;

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
    else // 将棋盤上にいないとき
    {
        // 駒がいないマスをtrueにする
        for (unsigned int row = 1; row <= rowSquareNum; row++)
        {
            for (unsigned int column = 1; column <= rowSquareNum; column++)
            {
                auto targetPiece = piecePosManager->GetPlacedPiece(row, column);
                if(targetPiece == nullptr) canPlaced[row - 1][column - 1] = true;
            }
        }

        // 以下、動くことのできる移動範囲によりルール上置けない位置をfalseにする
        // 最上段の変数を作る
        auto topRow = playerSide == PlayerSide::PLAYER_1 ?
            1 : rowSquareNum;

        // 歩
        if (piece->GetGameObjType() == GameObjType::PAWN)
        {
            // 歩が最上段に置かれるのを禁止する
            for (unsigned int column = 1; column <= rowSquareNum; column++)
            {
                canPlaced[topRow - 1][column - 1] = false;
            }

            // 二歩になる位置をfalseにする
            for (unsigned int row = 1; row <= rowSquareNum; row++)
            {
                for (unsigned int column = 1; column <= rowSquareNum; column++)
                {
                    auto targetPiece = piecePosManager->GetPlacedPiece(row, column);
                    if(targetPiece == nullptr) continue; // 何もいなければ次へ
                    auto isNotAlly = piece->GetPlayerSide() != playerSide;
                    if(isNotAlly) continue; // 味方の駒ではなければ次へ
                    auto isNotPawn = piece->GetGameObjType() != GameObjType::PAWN;
                    if(isNotPawn) continue; // 歩でなければ次へ
                    auto isPromotion = piece->GetIsPromotion();
                    if(isPromotion) continue; // と金であれば次へ
                    
                    // ここまで来たら二歩のため同列をfalseにする
                    for (unsigned int tempRow = 1; tempRow <= rowSquareNum; tempRow++)
                    {
                        canPlaced[tempRow - 1][column - 1] = false;
                    }
                }
            }
        }

        // 香車
        if (piece->GetGameObjType() == GameObjType::LANCE)
        {
            // 香が最上段に置かれるのを禁止する
            for (unsigned int column = 1; column <= rowSquareNum; column++)
            {
                canPlaced[topRow - 1][column - 1] = false;
            }
        }

        // 桂馬
        if (piece->GetGameObjType() == GameObjType::KNIGHT)
        {
            // 桂馬が最上段から2段に置かれるのを禁止する
            for (unsigned int column = 1; column <= rowSquareNum; column++)
            {
                canPlaced[topRow - 1][column - 1] = false;
                canPlaced[topRow + move.down - 1][column - 1] = false;
            }
        }
    }

    // 以下、王手等のルールを踏まえて修正する

    // 現在の王の位置がどのような攻撃を受けているか取得
    auto kingPlace        = piecePosManager->GetKingPlace(playerSide);
    auto kingAttackedBits = GetAttackedBits(piece->GetPlayerSide(), kingPlace.row, kingPlace.column);

    if (piece->GetGameObjType() == GameObjType::KING) // 王の場合
    {
        unsigned char tempRow;
        unsigned char tempColumn;

        // 下直進攻撃を受けている際は、上に移動できない
        if ((kingAttackedBits & PieceMovementBit::GetStraightDownBit()) > 0)
        {
            tempRow =    placedRow    + move.up;
            tempColumn = placedColumn;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) canPlaced[tempRow - 1][tempColumn - 1] = false;
        }
        // 左直進攻撃を受けている際は、右に移動できない
        if ((kingAttackedBits & PieceMovementBit::GetStraightLeftBit()) > 0)
        {
            tempRow =    placedRow;
            tempColumn = placedColumn + move.right;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) canPlaced[tempRow - 1][tempColumn - 1] = false;
        }
        // 右直進攻撃を受けている際は、左に移動できない
        if ((kingAttackedBits & PieceMovementBit::GetStraightRightBit()) > 0)
        {
            tempRow =    placedRow;
            tempColumn = placedColumn + move.left;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) canPlaced[tempRow - 1][tempColumn - 1] = false;
        }
        // 上直進攻撃を受けている際は、下に移動できない
        if ((kingAttackedBits & PieceMovementBit::GetStraightUpBit()) > 0)
        {
            tempRow =    placedRow    + move.down;
            tempColumn = placedColumn;
            if (GetIsRowAndColumnCorrect(tempRow, tempColumn)) canPlaced[tempRow - 1][tempColumn - 1] = false;
        }

        // 移動先が攻撃されていた場合は移動出来ない
        for (unsigned int row = 1; row <= rowSquareNum; row++)
        {
            for (unsigned int column = 1; column <= rowSquareNum; column++)
            {
                if(!canPlaced[row - 1][column - 1]) continue;
                auto distinationAttackedBits = GetAttackedBits(playerSide, row, column);
                if(distinationAttackedBits > 0) canPlaced[row - 1][column - 1] = false;
            }
        }
    }
    else // 王以外の場合
    {
        if (kingAttackedBits > 0) // 王が攻撃されている場合
        {
            // 王がいくつの駒から攻撃を受けているか確認
            unsigned char attackedCount = 0;
            for (unsigned int i = 0; i < (sizeof(i) * 8); i++)
            {
                
                if((kingAttackedBits & (1 << i)) > 0) attackedCount++;
            }

            if (attackedCount > 1) // 複数攻撃されていたら、王以外の駒は動けないようにするため全てfalse
            {
                for (unsigned int row = 1; row <= rowSquareNum; row++)
                {
                    for (unsigned int column = 1; column <= rowSquareNum; column++)
                    {
                        canPlaced[row - 1][column - 1] = false;
                    }
                }
            }
            else // 王への複数攻撃でなければ、王手を防げない動きをfalseにする
            {
                // 王への直進攻撃でなければ、その攻撃している駒の位置にのみ動くことを許可する
                unsigned char targetRow    = kingPlace.row;
                unsigned char targetColumn = kingPlace.column;
                bool isNotStraightAttack = false;

                // 下からの攻撃
                if ((kingAttackedBits & PieceMovementBit::GetDownBit()) > 0)
                {
                    targetRow += move.down; 
                    isNotStraightAttack = true;
                }
                // 左からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetLeftBit()) > 0)
                {
                    targetColumn += move.left; 
                    isNotStraightAttack = true;
                }
                // 右からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetRightBit()) > 0)
                {
                    targetColumn += move.right; 
                    isNotStraightAttack = true;
                }
                // 上からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetUpBit()) > 0)
                {
                    targetRow += move.up; 
                    isNotStraightAttack = true;
                }
                // 左下からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetLeftDownBit()) > 0)
                {
                    targetRow    += move.down; 
                    targetColumn += move.left; 
                    isNotStraightAttack = true;
                }
                // 右下からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetRightDownBit()) > 0)
                {
                    targetRow    += move.down; 
                    targetColumn += move.right; 
                    isNotStraightAttack = true;
                }
                // 左上からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetLeftUpBit()) > 0)
                {
                    targetRow    += move.up; 
                    targetColumn += move.left; 
                    isNotStraightAttack = true;
                }
                // 右上からの攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetRightUpBit()) > 0)
                {
                    targetRow    += move.up; 
                    targetColumn += move.right; 
                    isNotStraightAttack = true;
                }

                // 対象の位置への動きが可能であれば、trueのまま残す
                if (isNotStraightAttack)
                {
                    for (unsigned int row = 1; row <= rowSquareNum; row++)
                    {
                        for (unsigned int column = 1; column <= rowSquareNum; column++)
                        {
                            if ((canPlaced[row - 1][column - 1] == true) && (row == targetRow) && (column == targetColumn))
                            {
                                // 対象の位置はなにもしない
                            }
                            else // 対象の位置以外は全てfalse
                            {
                                canPlaced[row - 1][column - 1] = false;
                            }
                        }
                    }
                }

                // 直進攻撃への対処処理をする
                char offsetRow    = 0;
                char offsetColumn = 0;
                isNotStraightAttack = true;
                // 下からの直進攻撃
                if ((kingAttackedBits & PieceMovementBit::GetStraightDownBit()) > 0)
                {
                    offsetRow += move.down;
                }
                // 左からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightLeftBit()) > 0)
                {
                    offsetColumn += move.left;
                    isNotStraightAttack = false;
                }
                // 右からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightRightBit()) > 0)
                {
                    offsetColumn += move.right;
                    isNotStraightAttack = false;
                }
                // 上からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightUpBit()) > 0)
                {
                    offsetRow += move.up;
                    isNotStraightAttack = false;
                }
                // 左下からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightLeftDownBit()) > 0)
                {
                    offsetRow    += move.down;
                    offsetColumn += move.left;
                    isNotStraightAttack = false;
                }
                // 右下からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightRightDownBit()) > 0)
                {
                    offsetRow    += move.down;
                    offsetColumn += move.right;
                    isNotStraightAttack = false;
                }
                // 左上からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightLeftUpBit()) > 0)
                {
                    offsetRow    += move.up;
                    offsetColumn += move.left;
                    isNotStraightAttack = false;
                }
                // 右上からの直進攻撃
                else if ((kingAttackedBits & PieceMovementBit::GetStraightRightUpBit()) > 0)
                {
                    offsetRow    += move.up;
                    offsetColumn += move.right;
                    isNotStraightAttack = false;
                }
                // 直進攻撃の経路および攻撃者のマスへの移動をtrueのまま残す
                if (!isNotStraightAttack)
                {
                    for (unsigned int row = 1; row <= rowSquareNum; row++)
                    {
                        for (unsigned int column = 1; column <= rowSquareNum; column++)
                        {
                            targetRow    = kingPlace.row    + offsetRow;
                            targetColumn = kingPlace.column + offsetColumn;
                            bool isTarget = false;

                            while (GetIsRowAndColumnCorrect(targetRow, targetColumn)) // 将棋盤上に収まっているか確認
                            {
                                if ((row == targetRow) && (column == targetColumn))
                                {
                                    // 対象の位置を発見したらフラグをオンにして処理を抜ける
                                    isTarget = true;
                                    break;
                                }

                                // 駒を見つけらたら処理を抜ける
                                if(piecePosManager->GetPlacedPiece(targetRow, targetColumn) != nullptr) break;

                                // 次の位置を走査する
                                targetRow    += offsetRow;
                                targetColumn += offsetColumn;
                            }

                            // 対象の位置でなければfalse
                            if(!isTarget) canPlaced[row - 1][column - 1] = false;
                        }
                    }
                }

            }
        }

        // 移動することで王が攻撃される移動をfalseにする
        // 直進攻撃を受けているか確認する
        auto attackedBits = GetAttackedBits(playerSide, placedRow, placedColumn);

        // 直進攻撃の先に王がいるか確認し、位置に応じて動けない範囲を禁止する
        bool isCanMoveVertical          = true;
        bool isCanMoveHorizontal        = true;
        bool isCanMoveDiagonalRightUp   = true;
        bool isCanMoveDiagonalRightDown = true;

        // 下から直進攻撃を受けているなら、上側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightDownBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.up;
            unsigned char tempColumn = placedColumn;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、縦以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveHorizontal        = false;
                        isCanMoveDiagonalRightUp   = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow += move.up;
            }
        }

        // 左から直進攻撃を受けているなら、右側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightLeftBit()) > 0)
        {
            unsigned char tempRow    = placedRow;
            unsigned char tempColumn = placedColumn + move.right;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、横以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical          = false;
                        isCanMoveDiagonalRightUp   = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempColumn += move.right;
            }
        }

        // 右から直進攻撃を受けているなら、左側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightRightBit()) > 0)
        {
            unsigned char tempRow    = placedRow;
            unsigned char tempColumn = placedColumn + move.left;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、横以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical          = false;
                        isCanMoveDiagonalRightUp   = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempColumn += move.left;
            }
        }

        // 上から直進攻撃を受けているなら、下側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightUpBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.down;
            unsigned char tempColumn = placedColumn;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、縦以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveHorizontal        = false;
                        isCanMoveDiagonalRightUp   = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow += move.down;
            }
        }

        // 左下から直進攻撃を受けているなら、右上側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightLeftDownBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.up;
            unsigned char tempColumn = placedColumn + move.right;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、右上（左下）以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical          = false;
                        isCanMoveHorizontal        = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow    += move.up;
                tempColumn += move.right;
            }
        }

        // 右下から直進攻撃を受けているなら、左上側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightRightDownBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.up;
            unsigned char tempColumn = placedColumn + move.left;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、右上（左下）以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical        = false;
                        isCanMoveHorizontal      = false;
                        isCanMoveDiagonalRightUp = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow    += move.up;
                tempColumn += move.left;
            }
        }

        // 左上から直進攻撃を受けているなら、右下側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightLeftUpBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.down;
            unsigned char tempColumn = placedColumn + move.right;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、右上（左下）以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical        = false;
                        isCanMoveHorizontal      = false;
                        isCanMoveDiagonalRightUp = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow    += move.down;
                tempColumn += move.right;
            }
        }

        // 右上から直進攻撃を受けているなら、左下側に自分側の王がいるか確認
        if ((attackedBits & PieceMovementBit::GetStraightRightUpBit()) > 0)
        {
            unsigned char tempRow    = placedRow    + move.down;
            unsigned char tempColumn = placedColumn + move.left;

            while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
            {
                // 駒がいるか確認する
                auto targetPiece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
                auto isNotNull   = targetPiece != nullptr;

                if (isNotNull) // 駒がいるなら、その駒が自分側の王か確認し、処理を抜ける
                {
                    auto isKing = targetPiece->GetGameObjType() == GameObjType::KING;
                    auto isAlly = targetPiece->GetPlayerSide()  == playerSide;
                    
                    // 自分側の王であれば、右上（左下）以外をfalseに
                    if (isKing && isAlly)
                    {
                        isCanMoveVertical          = false;
                        isCanMoveHorizontal        = false;
                        isCanMoveDiagonalRightDown = false;
                    }

                    break;
                } 

                // 次を走査する
                tempRow    += move.down;
                tempColumn += move.left;
            }
        }

        // 移動禁止の範囲をfalseにする
        
        // 縦移動禁止
        if (!isCanMoveVertical)
        {
            for (unsigned char row = 1; row <= rowSquareNum; row++)
            {
                for (unsigned char column = 1; column <= rowSquareNum; column++)
                {
                    char          offsetRow    = move.up;
                    char          offsetColumn = 0;
                    unsigned char tempRow      = placedRow    + offsetRow;
                    unsigned char tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }

                    offsetRow    = move.down;
                    offsetColumn = 0;
                    tempRow      = placedRow    + offsetRow;
                    tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }
                }
            }
        }

        // 横移動禁止
        if (!isCanMoveHorizontal)
        {
            for (unsigned char row = 1; row <= rowSquareNum; row++)
            {
                for (unsigned char column = 1; column <= rowSquareNum; column++)
                {
                    char          offsetRow    = 0;
                    char          offsetColumn = move.right;
                    unsigned char tempRow      = placedRow    + offsetRow;
                    unsigned char tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }

                    offsetRow    = 0;
                    offsetColumn = move.left;
                    tempRow      = placedRow    + offsetRow;
                    tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }
                }
            }
        }

        // 右上(右下)移動禁止
        if (!isCanMoveDiagonalRightUp)
        {
            for (unsigned char row = 1; row <= rowSquareNum; row++)
            {
                for (unsigned char column = 1; column <= rowSquareNum; column++)
                {
                    char          offsetRow    = move.up;
                    char          offsetColumn = move.right;
                    unsigned char tempRow      = placedRow    + offsetRow;
                    unsigned char tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }

                    offsetRow    = move.down;
                    offsetColumn = move.left;
                    tempRow      = placedRow    + offsetRow;
                    tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }
                }
            }
        }

        // 右下(左上)移動禁止
        if (!isCanMoveDiagonalRightDown)
        {
            for (unsigned char row = 1; row <= rowSquareNum; row++)
            {
                for (unsigned char column = 1; column <= rowSquareNum; column++)
                {
                    char          offsetRow    = move.down;
                    char          offsetColumn = move.right;
                    unsigned char tempRow      = placedRow    + offsetRow;
                    unsigned char tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }

                    offsetRow    = move.up;
                    offsetColumn = move.left;
                    tempRow      = placedRow    + offsetRow;
                    tempColumn   = placedColumn + offsetColumn;
                    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
                    {
                        // 対象のマスをfalseにする
                        if((row == tempRow) && (column == tempColumn)) canPlaced[row - 1][column - 1] = false;

                        // 次を操作 
                        tempRow    += offsetRow;
                        tempColumn += offsetColumn;
                    }
                }
            }
        }

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
bool RuleManager::GetIsWinning(PlayerSide playerSide)
{
    //auto& app = Application::GetInstance();
    //auto piecePosManager = app.GetPiecePosManager();

    //// 相手の玉を探す
    //PlayerSide opponentPlayerSide = playerSide == PlayerSide::PLAYER_1 ?
    //    PlayerSide::PLAYER_2 : PlayerSide::PLAYER_1;
    //auto opponentKingPlace = piecePosManager->GetKingPlace(opponentPlayerSide);
    //
    //// 攻撃されているかどうかを返す
    //auto attackedBits = GetAttackedBits(opponentPlayerSide, opponentKingPlace.row, opponentKingPlace.column);

    return false;
}

// 成りが可能かどうか確認する
bool RuleManager::GetCanPromotion(I_Piece* piece, unsigned char row, unsigned char column)
{
    // 駒が王や金であれば、成りは不可能
    auto pieceType = piece->GetGameObjType();
    auto isKingOrGold = (pieceType == GameObjType::KING) || (pieceType == GameObjType::GOLD);
    if(isKingOrGold) return false;

    // 既に成っているのなら成りは不可
    auto isPromotioned = piece->GetIsPromotion();
    if(isPromotioned) return false;

    // 駒が将棋盤上に無い場所から動かされたのなら、成りは不可能
    auto& app             = Application::GetInstance();
    auto  piecePosManager = app.GetPiecePosManager();
    auto  isPlacedOnBoard = piecePosManager->GetIsPiecePlacedOnBoard(piece);
    if(!isPlacedOnBoard) return false;

    // 相手側の陣地3段以内にいなければ成りは不可能
    auto board           = app.GetGameObjects()->GetBoard();
    unsigned char columnSquareNum;
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_99:
            columnSquareNum = 9;
            break;

        default:
            columnSquareNum = 1;
            break;
    }
    auto playerSide = piece->GetPlayerSide();
    auto min = playerSide == PlayerSide::PLAYER_1 ?
        1 : columnSquareNum - 2;
    auto max = playerSide == PlayerSide::PLAYER_1 ?
        3 : columnSquareNum;
    auto isOpponentPos = (min <= row) && (row <= max);
    if(!isOpponentPos) return false;

    // ここまで来たら成り可能
    return true;
}

// 成りが強制かどうか確認する
bool RuleManager::GetIsForcedPromotion(I_Piece* piece, unsigned char row, unsigned char column)
{
    // 成りができなければfalse
    if(!GetCanPromotion(piece, row, column)) return false;

    // 最上段の変数を作る
    auto playerSide = piece->GetPlayerSide();
    auto board      = Application::GetInstance().GetGameObjects()->GetBoard();
    auto rowNum     = board->GetBoardSquareNum();
    auto topRow     = playerSide == PlayerSide::PLAYER_1 ?
        1 : rowNum;

    // プレイヤーにとっての上下左右のプラスマイナスを取得
    auto move = GetMoveForPlayer(playerSide);

    // 以下、駒に応じて強制かどうか確認
    auto pieceType = piece->GetGameObjType();

    switch (pieceType)
    {
        case GameObjType::PAWN:
        case GameObjType::LANCE:
            // 最上段であれば強制
            if(row == topRow) return true;
            break;

        case GameObjType::KNIGHT:
            // 最上段から2行であれば強制
            if(row == topRow || row == topRow + move.down) return true;
            break;

        default:
            break;
    }

    return false;
}

// プレイヤーが王手されているか確認
bool RuleManager::GetIsChecked(PlayerSide playerSide)
{
    auto& app = Application::GetInstance();
    auto piecePosManager = app.GetPiecePosManager();

    // 王を探す
    auto kingPlace = piecePosManager->GetKingPlace(playerSide);
    
    // 攻撃されているかどうかを返す
    auto attackedBits = GetAttackedBits(playerSide, kingPlace.row, kingPlace.column);

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

    // 左下から直進攻撃をされているか確認
    tempRow    = row    + move.down;
    tempColumn = column + move.left;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左下直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightLeftDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow    += move.down;
        tempColumn += move.left;
    }

    // 右下から直進攻撃をされているか確認
    tempRow    = row    + move.down;
    tempColumn = column + move.right;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右下直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightRightDownBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow    += move.down;
        tempColumn += move.right;
    }

    // 左上から直進攻撃をされているか確認
    tempRow    = row    + move.up;
    tempColumn = column + move.left;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、左上直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightLeftUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow    += move.up;
        tempColumn += move.left;
    }

    // 右上から直進攻撃をされているか確認
    tempRow    = row    + move.up;
    tempColumn = column + move.right;
    while (GetIsRowAndColumnCorrect(tempRow, tempColumn)) // 将棋盤上に収まっているか確認
    {
        // 駒がいるか確認する
        auto piece = piecePosManager->GetPlacedPiece(tempRow, tempColumn);
        auto isNotNull = piece != nullptr;
        if (isNotNull)
        {
            // その駒が相手の駒であり、右上直進の移動が可能であれば、攻撃されていることを記録
            auto isOpponentPiece = piece->GetPlayerSide() != playerSide;
            auto movementBit = PieceMovementBit::GetStraightRightUpBit();
            auto isPossibleMovement = IsPossibleMovement(piece, movementBit);
            if(isOpponentPiece && isPossibleMovement) attackedBits |= movementBit;

            // 駒を見つけたので、処理を抜ける
            break;
        }

        // 次のマスを走査する
        tempRow    += move.up;
        tempColumn += move.right;
    }

    return attackedBits;
}