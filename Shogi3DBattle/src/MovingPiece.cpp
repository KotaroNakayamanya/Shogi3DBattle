#include"MovingPiece.h"
#include"MoveForward.h"
#include"MoveLeft.h"
#include"MoveBack.h"
#include"MoveRight.h"
#include"ViewRotation.h"
#include"Application.h"


// 操作開始
ISceneState* MovingPiece::ExeOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    ISceneState* newSceneState = nullptr;

    if(inputMemory & InputHandler::MOUSE_MOVE) // マウス操作処理
    {
        newSceneState = ExeMouseMove(cursorXMove, cursorYMove);
    }
    if(inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        newSceneState = ExeCancelButton();
    if(inputMemory & InputHandler::UP)        // 上ボタン処理
        newSceneState = ExeUpButton();
    if(inputMemory & InputHandler::LEFT)      // 左ボタン処理
        newSceneState = ExeLeftButton();
    if(inputMemory & InputHandler::DOWN)      // 下ボタン処理
        newSceneState = ExeDownButton();
    if(inputMemory & InputHandler::RIGHT)     // 右ボタン処理
        newSceneState = ExeRightButton();

    return newSceneState;
}

// 決定ボタン
ISceneState* MovingPiece::ExeDecisionButton()
{
    return this;
}

// キャンセルボタン処理
ISceneState* MovingPiece::ExeCancelButton()
{
    DestroyWindow(_hwnd);
    return this;
}

// 上ボタン処理
ISceneState* MovingPiece::ExeUpButton()
{
    _piece->MoveY(0.1f);
    _viewMat->MoveFocus(0, 0.1f, 0);
    _viewMat->MoveEye   (0, 0.1f, 0);
    //_moveForward->Exe();
    //_moveTargetForward->Exe();
    //_moveEyeForward->Exe();

    return this;
}

// 左ボタン処理
ISceneState* MovingPiece::ExeLeftButton()
{
    _piece->MoveX(-0.1f);
    _viewMat->MoveFocus(-0.1f, 0, 0);
    _viewMat->MoveEye   (-0.1f, 0, 0);
    //_moveLeft->Exe();
    //_moveTargetForward->Exe();
    //_moveEyeForward->Exe();

    return this;
}

// 下ボタン処理
ISceneState* MovingPiece::ExeDownButton()
{
    _piece->MoveY(-0.1f);
    _viewMat->MoveFocus(0, -0.1f, 0);
    _viewMat->MoveEye   (0, -0.1f, 0);
    //_moveBack->Exe();
    //_moveTargetForward->Exe();
    //_moveEyeForward->Exe();

    return this;
}
// 右ボタン処理
ISceneState* MovingPiece::ExeRightButton()
{
    _piece->MoveX(0.1f);
    _viewMat->MoveFocus(0.1f, 0, 0);
    _viewMat->MoveEye   (0.1f, 0, 0);
    //_moveRight->Exe();
    //_moveTargetForward->Exe();
    //_moveEyeForward->Exe();

    return this;
}

// カーソル操作処理
ISceneState* MovingPiece::ExeMouseMove(int xMove, int yMove)
{
    float fx = xMove / 1000.0f;
    float fy = yMove / 1000.0f;

    _viewMat->RotationH(fx);
    _viewMat->RotationV(fy);
    //_mouseMove->Exe(xMove, yMove);
    return this;
}




MovingPiece::MovingPiece(Piece* piece)
{
    Application& app = Application::GetInstance();

    _hwnd = app.GetHWND();
    _piece = piece;
    _viewMat = app.GetViewMat();

    

    
}

MovingPiece::~MovingPiece(){}