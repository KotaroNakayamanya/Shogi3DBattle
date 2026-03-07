#include"MovePiece.h"

// 決定
ISceneState* MovePiece::ExeDecision()
{
    return this;
}
// キャンセル
ISceneState* MovePiece::ExeCancel()
{
    DestroyWindow(_hwnd);
    return this;
}
// 上
ISceneState* MovePiece::ExeUp()
{
    DestroyWindow(_hwnd);
    return this;
}

// 左 
ISceneState* MovePiece::ExeLeft()
{
    DestroyWindow(_hwnd);
    return this;
}
// 下
ISceneState* MovePiece::ExeDown()
{
    DestroyWindow(_hwnd);
    return this;
}
// 右
ISceneState* MovePiece::ExeRight()
{
    DestroyWindow(_hwnd);
    return this;
}
// マウス操作
ISceneState* MovePiece::ExeMouseMove()
{
    DestroyWindow(_hwnd);
    return this;
}




MovePiece::MovePiece(HWND hwnd) : MovePiece()
{
    _hwnd = hwnd;
}

MovePiece::MovePiece(){}
MovePiece::~MovePiece(){}