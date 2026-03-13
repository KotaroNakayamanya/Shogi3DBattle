#include"MovingPiece.h"
#include"MoveForward.h"
#include"MoveLeft.h"
#include"MoveBack.h"
#include"MoveRight.h"
#include"ViewRotation.h"
#include"Application.h"

// 決定ボタン処理
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
    _moveForward->Exe();
    return this;
}

// 左ボタン処理
ISceneState* MovingPiece::ExeLeftButton()
{
    _moveLeft->Exe();
    return this;
}

// 下ボタン処理
ISceneState* MovingPiece::ExeDownButton()
{
    _moveBack->Exe();
    return this;
}
// 右ボタン処理
ISceneState* MovingPiece::ExeRightButton()
{
    _moveRight->Exe();
    return this;
}

// カーソル操作処理
ISceneState* MovingPiece::ExeMouseMove(int xMove, int yMove)
{
    _mouseMove->Exe(xMove, yMove);
    return this;
}




MovingPiece::MovingPiece(Piece* piece)
{
    Application& app = Application::GetInstance();

    _hwnd = app.GetHWND();
   
    _moveForward = std::make_unique<MoveForward>(piece);
    _moveLeft    = std::make_unique<MoveLeft>(piece);
    _moveBack    = std::make_unique<MoveBack>(piece);
    _moveRight   = std::make_unique<MoveRight>(piece);

    ViewMat* viewMat = app.GetViewMat();
    _mouseMove   = std::make_unique<ViewRotation>(viewMat);

    
}

MovingPiece::~MovingPiece(){}