#pragma once

#include"ISceneState.h"
#include"Piece.h"
#include"Camera.h"

class MovingPiece : public ISceneState
{
private:
    Piece* _piece;     // 操作している駒
    Camera* _mainCamera; // メインカメラ

    DirectX::XMMATRIX _startWorldMat; // 初期ワールド行列
    //DirectX::XMFLOAT3 _startCameraPos;      // 初期カメラ位置
    //DirectX::XMFLOAT3 _startFocusPos;    // 初期フォーカス位置

    bool _isMoved; // 駒が動いたかどうか確認

    ISceneState* ExeDecisionButton(); // 決定ボタン処理
    ISceneState* ExeCancelButton(); // キャンセルボタン処理
    void ExeMouseMove(int xMove, int yMove); // カーソル操作処理

    void MovePieceAndCamera(DirectX::XMFLOAT3 vec); // 駒とカメラを動かす

    MovingPiece(){}

public:
    // 駒操作シーン動作
    ISceneState* ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    MovingPiece(Piece* piece);
    ~MovingPiece();
};