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

    auto board     = app.GetBoard();
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

    auto piecePosManager = Application::GetInstance().GetPiecePosManager(); // 駒の位置マネージャ取得
    for (unsigned int row = 1; row <= squareNum; row++)
    {
        for (unsigned int column = 1; column<= squareNum; column++)
        {
            auto piece = piecePosManager->GetPlacedPiece(row, column); // 対象マスに位置する駒を取得
            if(!piece) continue; // 駒がいなければスキップ

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
    if(inputMemory & InputHandler::DECISION)
        return ExeDecisionButtonProcess();
    if(inputMemory & InputHandler::CANCEL)
        return ExeCancelButton();

    return nullptr;
}

// キャンセルボタン処理
std::unique_ptr<I_SceneState> SelectingPieceScene::ExeCancelButton()
{
    std::unique_ptr<I_SceneState> newSceneState = std::make_unique<TitleScene>(); // スタートメニューに遷移する

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveRClick();

    return newSceneState;
}




SelectingPieceScene::SelectingPieceScene()
{
    _mainCamera     = Application::GetInstance().GetMainCamera();
    auto mapCamera  = Application::GetInstance().GetMapCamera();

    // 現在のメインカメラのパース付きプロジェクション行列を保存する
    auto mainPersProjMat = static_cast<PersProjMat*>(_mainCamera->GetProjMat());
    _oldPersProjMat = *mainPersProjMat;
    
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

SelectingPieceScene::~SelectingPieceScene()
{
    // カメラをパース付きプロジェクション行列に戻す
    PersProjMat* persProjMat = new PersProjMat;
    *persProjMat = _oldPersProjMat;
    _mainCamera->SetProjMat(persProjMat);
}