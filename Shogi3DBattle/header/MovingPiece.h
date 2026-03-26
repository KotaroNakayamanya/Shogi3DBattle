#pragma once

#include"ISceneState.h"
#include"Piece.h"
#include"Camera.h"
#include<Windows.h>

class MovingPiece : public ISceneState
{
private:
    Piece* _piece;     // 操作している駒
    Camera* _camera; // カメラ
    HWND _hwnd;        // ウインドウハンドル

    ISceneState* ExeDecisionButton(); // 決定ボタン処理
    ISceneState* ExeCancelButton(); // キャンセルボタン処理
    ISceneState* ExeUpButton(); // 上ボタン処理
    ISceneState* ExeLeftButton(); // 左ボタン処理
    ISceneState* ExeDownButton(); // 下ボタン処理
    ISceneState* ExeRightButton(); // 右ボタン処理

    void MovePieceAndCamera(DirectX::XMFLOAT3 vec); // 駒とカメラを動かす

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