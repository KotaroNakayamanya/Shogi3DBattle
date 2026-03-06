#include"MovePiece.h"

// 上
SceneState* MovePiece::ExeUpCommand()
{
    DestroyWindow(_hwnd);
    return this;
}

// 左 
SceneState* MovePiece::ExeLeftCommand()
{
    return this;
}
// 下
SceneState* MovePiece::ExeDownCommand()
{
    return this;
}
// 右
SceneState* MovePiece::ExeRightCommand()
{
    return this;
}
// マウス操作
SceneState* MovePiece::ExeMouseCommand()
{
    return this;
}
// 決定
SceneState* MovePiece::ExeDecisionCommand()
{
    return this;
}
// キャンセル
SceneState* MovePiece::ExeCancelCommand()
{
    return this;
}




MovePiece::MovePiece(HWND hwnd) : MovePiece()
{
    _hwnd = hwnd;
}

MovePiece::MovePiece(){}
MovePiece::~MovePiece(){}