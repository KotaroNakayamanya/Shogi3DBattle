#pragma once

#include<memory>
#include"ISceneState.h"
#include"ICommand.h"
#include"IMouse.h"
#include"Piece.h"
#include"ViewMat.h"
#include<Windows.h>
#include"MoveTargetForward.h"
#include"MoveEyeForward.h"

class MovingPiece : public ISceneState
{
private:
    Piece* _piece;     // 操作している駒
    ViewMat* _viewMat; // カメラ用途のビュー行列
    HWND _hwnd;        // ウインドウハンドル

    ISceneState* ExeDecisionButton(); // 決定ボタン処理
    ISceneState* ExeCancelButton(); // キャンセルボタン処理
    ISceneState* ExeUpButton(); // 上ボタン処理
    ISceneState* ExeLeftButton(); // 左ボタン処理
    ISceneState* ExeDownButton(); // 下ボタン処理
    ISceneState* ExeRightButton(); // 右ボタン処理
    ISceneState* ExeMouseMove(int xMove, int yMove); // カーソル操作処理

public:
    ISceneState* ExeOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    MovingPiece(Piece* piece);
    ~MovingPiece();
};