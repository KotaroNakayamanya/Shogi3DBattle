#include"SelectingPieceScene.h"
#include"Application.h"
#include"MovingPieceScene.h"
#include"TitleScene.h"
#include"PersProjMat.h"
#include"NonePersProjMat.h"

// ボタンUIセット
void SelectingPieceScene::SetButton()
{
    auto& app = Application::GetInstance();

    auto board     = app.GetGameObjects()->GetBoard();
    auto squareNum = board->GetBoardSquareNum();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    auto squareSize     = windowHeight / static_cast<float>(squareNum + 2); // マス１辺のサイズ
    auto halfSquareSize = squareSize / 2.0f;                                // マス半分のサイズ

    auto boardSize = (squareSize*squareNum) + (halfSquareSize*2); // 将棋盤サイズ

    auto boardRightTopX = windowWidth - ((windowWidth-boardSize)/2.0f);
    auto boardRightTopY = halfSquareSize;
    auto square1x1LeftTopX = boardRightTopX - halfSquareSize - squareSize;
    auto square1x1LeftTopY = boardRightTopY + halfSquareSize;

    // 駒を選択できるよう配置する
    auto piecePosManager = Application::GetInstance().GetPiecePosManager(); // 駒の位置マネージャ取得
    auto currentPlayer = app.GetCurrentPlayerTurn();
    
    // 将棋盤上の駒
    for (unsigned int row = 1; row <= squareNum; row++)
    {
        for (unsigned int column = 1; column<= squareNum; column++)
        {
            auto piece = piecePosManager->GetPlacedPiece(row, column); // 対象マスに位置する駒を取得
            if(!piece) continue; // 駒がいなければスキップ
            auto isCurrentPlayerTurnPiece = piece->GetPlayerSide() != currentPlayer;
            if(isCurrentPlayerTurnPiece) continue; // 操作プレイヤーの駒でなければスキップ

            auto squareLeftTopX     = square1x1LeftTopX - (column-1)*squareSize; // マス左上X座標
            auto squareLeftTopY     = square1x1LeftTopY + (row   -1)*squareSize; // マス左上Y座標
            auto squareRightBottomX = squareLeftTopX + squareSize;
            auto squareRightBottomY = squareLeftTopY + squareSize;

            D2D1_RECT_F rect = {
                squareLeftTopX,
                squareLeftTopY,
                squareRightBottomX,
                squareRightBottomY
            };
            
            app.PushPieceButton(PieceButtonType::SELECT_PIECE_BUTTON, rect, piece);
        }
    }

    // プレイヤーの駒置き台の駒
    auto playerSideBoard = piecePosManager->GetPiecePlacedOnSideBoard(currentPlayer);
    auto piecesNum = playerSideBoard.size();
    auto sideBoardLeftTopX = currentPlayer == PlayerSide::PLAYER_1 ?
        boardRightTopX : boardRightTopX - squareSize*11;
    auto sideBoardLeftTopY = currentPlayer == PlayerSide::PLAYER_1 ?
        boardRightTopY + squareSize*7 : boardRightTopY + squareSize*2;
    
    for(unsigned int i = 0; i < piecesNum; i++)
    {
        // 駒の数を確認し、1つ以上なら最後に追加された駒のボタン設置
        auto& pieces   = playerSideBoard[i];
        auto  pieceNum = pieces.size();
        if (pieceNum > 0)
        {
            auto offsetRight = currentPlayer == PlayerSide::PLAYER_1 ?
                squareSize * (i%3) : -squareSize * (i%3);
            auto offsetDown = currentPlayer == PlayerSide::PLAYER_1 ?
                squareSize * (i/3) : -squareSize * (i/3);

            auto squareLeftTopX     = sideBoardLeftTopX + offsetRight;
            auto squareLeftTopY     = sideBoardLeftTopY + offsetDown;
            auto squareRightBottomX = squareLeftTopX + squareSize;
            auto squareRightBottomY = squareLeftTopY + squareSize;

            D2D1_RECT_F rect = {
                squareLeftTopX,
                squareLeftTopY,
                squareRightBottomX,
                squareRightBottomY
            };

            app.PushPieceButton(PieceButtonType::SELECT_PIECE_BUTTON, rect, pieces[pieceNum - 1]);
        }
    }

    // タイトルに戻るボタンを追加
    float height = 60.0f;
    float width  = 280.0f;
    float offset = 10.0f;
    float left   = offset;
    float top    = windowHeight - height - offset;
    float right  = left + width;
    float bottom = top  + height;
    D2D1_RECT_F rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::BACK_TITLE_BUTTON, rect);


}

// テキストUIセット
void SelectingPieceScene::SetTextUI()
{
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();
    auto dx12 = app.GetDX12();
    
    // 現在のプレイヤーのターンをテキスト表示
    float centerXPos;
    float centerYPos;
    Text2D text2D;
    text2D.brush = dx12->GetBlackBrush();
    text2D.textFormat = dx12->GetNormalTextFormat();
    auto playerTurn = app.GetCurrentPlayerTurn();
    switch (playerTurn)
    {
        case PlayerSide::PLAYER_1:
            text2D.text = L"先手のターン";
            centerXPos = windowWidth  / 8 * 1;
            centerYPos = windowHeight / 8 * 5;
            break;

        case PlayerSide::PLAYER_2:
            text2D.text = L"後手のターン";
            centerXPos = windowWidth  / 8 * 7;
            centerYPos = windowHeight / 8 * 1;
            break;

        default:
            text2D.text = L"???のターン";
            break;
    }

    auto width  = windowWidth  * 0.5f;
    auto height = windowHeight * 0.1f;

    auto left   = centerXPos - (width / 2.0f);
    auto right  = left + width;
    auto top    = centerYPos - (height / 2.0f);
    auto bottom = top + height;
    text2D.rect = {left, top, right, bottom};
    app.PushTextUI(text2D);

    // 王手されていたらテキスト追加
    if (app.GetIsPlayerChecked(playerTurn))
    {
        text2D.text = L"王手されてます";
        top    += height;
        bottom += height;
        text2D.rect = {left, top, right, bottom};
        text2D.brush = dx12->GetRedBrush();
        app.PushTextUI(text2D);
    }

    // 駒置き台の駒数を表示
    auto board     = app.GetGameObjects()->GetBoard();
    auto squareNum = board->GetBoardSquareNum();

    auto squareSize     = windowHeight / static_cast<float>(squareNum + 2); // マス１辺のサイズ
    auto halfSquareSize = squareSize / 2.0f;                                // マス半分のサイズ

    auto boardSize = (squareSize*squareNum) + (halfSquareSize*2); // 将棋盤サイズ

    auto boardRightTopX = windowWidth - ((windowWidth-boardSize)/2.0f);
    auto boardRightTopY = halfSquareSize;

    auto piecePosManager = app.GetPiecePosManager();

    text2D.brush = dx12->GetBlackBrush();

    auto player1SideBoard = piecePosManager->GetPiecePlacedOnSideBoard(PlayerSide::PLAYER_1);
    for (int i = 0; i < player1SideBoard.size(); i++)
    {
        int pieceNum = player1SideBoard[i].size();
        if (pieceNum > 0)
        {
            text2D.text = std::to_wstring(pieceNum);
            left   = boardRightTopX                - halfSquareSize*0.5f + squareSize*(i%3);
            top    = boardRightTopY + squareSize*7                       + squareSize*(i/3);
            right  = left + squareSize;
            bottom = top  + halfSquareSize;
            text2D.rect = {left, top, right, bottom};
            app.PushTextUI(text2D);
        }
    }
    auto player2SideBoard = piecePosManager->GetPiecePlacedOnSideBoard(PlayerSide::PLAYER_2);
    for (int i = 0; i < player2SideBoard.size(); i++)
    {
        int pieceNum = player2SideBoard[i].size();
        if (pieceNum > 0)
        {
            text2D.text = std::to_wstring(pieceNum);
            left   = boardRightTopX - squareSize*11 - halfSquareSize*0.5f - squareSize*(i%3);
            top    = boardRightTopY + squareSize* 2                       - squareSize*(i/3);
            right  = left + squareSize;
            bottom = top  + halfSquareSize;
            text2D.rect = {left, top, right, bottom};
            app.PushTextUI(text2D);
        }
    }

}

// 駒選択シーン動作
std::unique_ptr<I_SceneState> SelectingPieceScene::ExeSelectingButtonSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    auto& app = Application::GetInstance();

    // テキストセット
    if (!_isSetText)
    {
        SetTextUI();

            _isSetText = true;
    }

    // ボタンが選択されていなければエフェクト削除
    if (GetSelectedButton() == nullptr)
    {
        auto textures = app.GetTextures();
        textures->CreateCanMoveEffectTextures(nullptr);
    }
    else
    {
    }


    if (inputMemory & InputHandler::DECISION)
    {
        // ボタンによる遷移ができるのならカメラをパース付きプロジェクション行列に戻す
        auto buttonProcess = ExeDecisionButtonProcess();
        if (buttonProcess != nullptr)
        {
            PersProjMat* persProjMat = new PersProjMat;
            *persProjMat = _oldPersProjMat;
            _mainCamera->SetProjMat(persProjMat);
        }
        return buttonProcess;
    }
    if(inputMemory & InputHandler::CANCEL)
        return ExeCancelButton();

    return nullptr;
}

// キャンセルボタン処理
std::unique_ptr<I_SceneState> SelectingPieceScene::ExeCancelButton()
{
    //// カメラをパース付きプロジェクション行列に戻す
    //PersProjMat* persProjMat = new PersProjMat;
    //*persProjMat = _oldPersProjMat;
    //_mainCamera->SetProjMat(persProjMat);

    //// スタートメニューに遷移する
    //std::unique_ptr<I_SceneState> newSceneState = std::make_unique<TitleScene>(); 

    //auto inputHandler = Application::GetInstance().GetInputHandler();
    //inputHandler->RemoveRClick();

    //return newSceneState;

    return nullptr;
}




SelectingPieceScene::SelectingPieceScene() : _isSetText(false)
{
    auto& app       = Application::GetInstance();
    _mainCamera     = app.GetMainCamera();
    auto mapCamera  = app.GetMapCamera();

    // 現在のメインカメラのパース付きプロジェクション行列を保存する
    auto mainPersProjMat = static_cast<PersProjMat*>(_mainCamera->GetProjMat());
    _oldPersProjMat = *mainPersProjMat;

    //// マップカメラの向きを現在のターンのプレイヤーの向きにする
    //auto yVec = app.GetCurrentPlayerTurn() == PlayerSide::PLAYER_1 ?
    //    -1.0f : 1.0f;
    //DirectX::XMFLOAT3 up = {0.0f, yVec, 0.0f};
    //mapCamera->SetCameraUpVec(up);
    
    // メインカメラをマップカメラを基準にしたカメラにする
    // ビュー行列
    _mainCamera->SetCameraPos  (mapCamera->GetCameraPos());
    _mainCamera->SetFocusPos   (mapCamera->GetFocusPos());
    _mainCamera->SetCameraUpVec(mapCamera->GetCameraUpVec());
    // プロジェクション行列
    auto mapNonePersProjMat = static_cast<NonePersProjMat*>(mapCamera->GetProjMat());
    NonePersProjMat* nonePersProjMat = new NonePersProjMat();
    *nonePersProjMat = *mapNonePersProjMat;
    nonePersProjMat->SetWidth (mapNonePersProjMat->GetWidth() * 16.0f / 9.0f); // 横サイズは拡張
    _mainCamera->SetProjMat(nonePersProjMat);
}