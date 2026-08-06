#include"RuleManager.h"
#include"Application.h"
#include"PieceMovementBit.h"

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
    // プレイヤー１なら右上が1一(マイナス)、プレイヤー２なら右上が9九(プラス)
    char right = 0;
    char up    = 0;
    char left  = 0;
    char down  = 0;
    if (playerSide == PlayerSide::PLAYER_1)
    {
        right = -1;
        up    = -1;
        left  =  1;
        down  =  1;
    }
    else
    {
        right =  1;
        up    =  1;
        left  = -1;
        down  = -1;
    }


    // 値が1~9の値に収まってるかチェックする関数
    auto Is1to9 = [](char n)
    {
        return (1 <= n) && (n <= 9);
    };

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
    tempRow    = row    + down;
    tempColumn = column;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempColumn = column + left;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempColumn = column + right;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + up;
    tempColumn = column;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + down;
    tempColumn = column + left;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + down;
    tempColumn = column + right;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + up;
    tempColumn = column + left;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + up;
    tempColumn = column + right;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + up*2;
    tempColumn = column + left;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + up*2;
    tempColumn = column + right;
    if (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
    tempRow    = row    + down;
    tempColumn = column;
    while (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
        tempRow += down;
    }

    // 左から直進攻撃をされているか確認
    tempRow    = row;
    tempColumn = column + left;
    while (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
        tempColumn += left;
    }

    // 右から直進攻撃をされているか確認
    tempRow    = row;
    tempColumn = column + right;
    while (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
        tempColumn += right;
    }

    // 上から直進攻撃をされているか確認
    tempRow    = row    + up;
    tempColumn = column;
    while (Is1to9(tempRow) && Is1to9(tempColumn)) // 9×9マスに収まっているか確認
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
        tempRow += up;
    }

    return attackedBits;
}