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
    for (unsigned int row = 1; row <= squareNum; row++)
    {
        for (unsigned int column = 1; column<= squareNum; column++)
        {
            auto piece = piecePosManager->GetPlacedPiece(row, column); // 対象マスに位置する駒を取得
            if(!piece) continue; // 駒がいなければスキップ
            auto isCurrentPlayerTurnPiece = piece->GetPlayerSide() != app.GetCurrentPlayerTurn();
            if(isCurrentPlayerTurnPiece) continue; // 操作プレイヤーの駒でなければスキップ

            auto squareLeftTopX = square1x1LeftTopX - (column-1)*squareSize; // マス左上X座標
            auto squareLeftTopY = square1x1LeftTopY + (row   -1)*squareSize; // マス左上Y座標
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

    //auto squareLeftTopX = boardLeftBottomX + halfSquareSize;
    //auto squareLeftTopY = boardLeftBottomY - halfSquareSize - squareSize;
    //auto squareRightBottomX = squareLeftTopX + squareSize;
    //auto squareRightBottomY = squareLeftTopY + squareSize;

    //auto piecePosManager = Application::GetInstance().GetPiecePosManager(); // 駒の位置マネージャ取得
    //auto piece = piecePosManager->GetPlacedPiece(9, 5);


}

// 駒選択シーン動作
std::unique_ptr<I_SceneState> SelectingPieceScene::ExeSelectingButtonSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    // テキストセット
    if (!_isSetText)
    {
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();
    auto dx12 = app.GetDX12();
    
    Text2D text2D;
    text2D.brush = dx12->GetBlackBrush();
    text2D.textFormat = dx12->GetNormalTextFormat();

    float centerXPos;
    float centerYPos;

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

    // テキスト追加
    auto left   = centerXPos - (width / 2.0f);
    auto right  = left + width;
    auto top    = centerYPos - (height / 2.0f);
    auto bottom = top + height;
    text2D.rect = {left, top, right, bottom};
    app.PushTextUI(text2D);

    if (app.GetIsPlayerChecked(playerTurn))
    {
        text2D.text = L"王手されてます";
        top    += height;
        bottom += height;
        text2D.rect = {left, top, right, bottom};
        app.PushTextUI(text2D);
    }


    //auto offset = -5.0f;
    //text2D.rect = {left+offset, top+offset, right+offset, bottom+offset};
    //text2D.textFormat = dx12->GetTitleTextFormat();
    //text2D.brush = dx12->GetYellowBrush();
    //app.PushTextUI(text2D);

        _isSetText = true;
    }


    if (inputMemory & InputHandler::DECISION)
    {
        // カーソルが駒の上で決定ボタンを押したら
        // カメラをパース付きプロジェクション行列に戻す
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
    // カメラをパース付きプロジェクション行列に戻す
    PersProjMat* persProjMat = new PersProjMat;
    *persProjMat = _oldPersProjMat;
    _mainCamera->SetProjMat(persProjMat);

    // スタートメニューに遷移する
    std::unique_ptr<I_SceneState> newSceneState = std::make_unique<TitleScene>(); 

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveRClick();

    return newSceneState;
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