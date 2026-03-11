#include"MovingPiece.h"
#include"MoveForward.h"
#include"MoveLeft.h"
#include"MoveBack.h"
#include"MoveRight.h"

// 決定ボタン処理
ISceneState* MovingPiece::ExeDecisionButton()
{
    return this;
}

// キャンセルボタン処理
ISceneState* MovingPiece::ExeCancelButton()
{
    return this;
}

// カーソル操作処理
ISceneState* MovingPiece::ExeCursorOperation()
{
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





MovingPiece::~MovingPiece(){}

MovingPiece::MovingPiece(Piece* piece)
{
    _moveForward.reset(new MoveForward(piece));
    _moveLeft   .reset(new MoveLeft   (piece));
    _moveBack   .reset(new MoveBack   (piece));
    _moveRight  .reset(new MoveRight  (piece));
}