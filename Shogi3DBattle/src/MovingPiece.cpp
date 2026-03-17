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
    _piece->MoveY(0.1f);
    _viewMat->MoveTarget(0, 0.1f, 0);
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
    _viewMat->MoveTarget(-0.1f, 0, 0);
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
    _viewMat->MoveTarget(0, -0.1f, 0);
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
    _viewMat->MoveTarget(0.1f, 0, 0);
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
   
    //_moveForward = std::make_unique<MoveForward>(piece);
    //_moveLeft    = std::make_unique<MoveLeft>(piece);
    //_moveBack    = std::make_unique<MoveBack>(piece);
    //_moveRight   = std::make_unique<MoveRight>(piece);
    _piece = piece;
    _viewMat = app.GetViewMat();
    //_mouseMove   = std::make_unique<ViewRotation>(viewMat);
    //_moveTargetForward = std::make_unique<MoveTargetForward>(viewMat);
    //_moveEyeForward = std::make_unique<MoveEyeForward>(viewMat);

    

    
}

MovingPiece::~MovingPiece(){}