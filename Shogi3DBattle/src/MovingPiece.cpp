#include"MovingPiece.h"
#include"MoveForward.h"

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
    return this;
}

// 下ボタン処理
ISceneState* MovingPiece::ExeDownButton()
{
    return this;
}
// 右ボタン処理
ISceneState* MovingPiece::ExeRightButton()
{
    return this;
}




MovingPiece::MovingPiece()
{
    _moveForward = std::make_unique<MoveForward>();
}
MovingPiece::~MovingPiece(){}