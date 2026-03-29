#include"SelectingPiece.h"
#include"Application.h"
#include"MovingPiece.h"
#include"StartMenu.h"
#include"PersProjMat.h"
#include"NonePersProjMat.h"

// 駒選択シーン動作
ISceneState* SelectingPiece::ExeSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    if(inputMemory & InputHandler::DECISION)
        return ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)
        return ExeCancelButton();

    return this;
}

// 決定ボタン
ISceneState* SelectingPiece::ExeDecisionButton()
{
    ISceneState* newSceneState;
    auto& pieces = Application::GetInstance().GetPieces();

    newSceneState = new MovingPiece(pieces[0].get()); // 駒操作シーンに遷移する
    ReversProjMat(); // メインカメラをパース付きに戻す

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveLClick();

    return newSceneState;
}

// キャンセルボタン処理
ISceneState* SelectingPiece::ExeCancelButton()
{
    ISceneState* newSceneState;
    
    newSceneState = new StartMenu(); // スタートメニューに遷移する
    ReversProjMat(); // メインカメラをパース付きに戻す

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveRClick();

    return newSceneState;
}

// パース付きプロジェクション行列に戻す
void SelectingPiece::ReversProjMat()
{
    PersProjMat* persProjMat = new PersProjMat;
    *persProjMat = _oldPersProjMat;
    _mainCamera->SetProjMat(persProjMat);
}





SelectingPiece::SelectingPiece()
{
    _mainCamera     = Application::GetInstance().GetMainCamera();
    auto mapCamera  = Application::GetInstance().GetMapCamera();

    // 現在のメインカメラのパース付きプロジェクション行列を保存する
    auto mainPersProjMat = static_cast<PersProjMat*>(_mainCamera->GetProjMat());
    _oldPersProjMat = *mainPersProjMat;
    
    // メインカメラのカメラ設定をマップカメラの設定にする
    _mainCamera->SetCameraPos  (mapCamera->GetCameraPos());
    _mainCamera->SetFocusPos   (mapCamera->GetFocusPos());
    _mainCamera->SetCameraUpVec(mapCamera->GetCameraUpVec());
    // メインカメラをマップカメラのカメラを基準にパースのついていないカメラにする
    auto mapNonePersProjMat = static_cast<NonePersProjMat*>(mapCamera->GetProjMat());
    NonePersProjMat* nonePersProjMat = new NonePersProjMat();
    *nonePersProjMat = *mapNonePersProjMat;
    nonePersProjMat->SetWidth (mapNonePersProjMat->GetWidth() * 16.0f / 9.0f); // 横サイズは拡張
    _mainCamera->SetProjMat(nonePersProjMat);
}

SelectingPiece::~SelectingPiece(){}