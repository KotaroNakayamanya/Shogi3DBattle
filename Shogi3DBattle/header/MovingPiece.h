#pragma once

#include"I_SceneState.h"
#include"I_Piece.h"
#include"Camera.h"

class MovingPiece : public I_SceneState
{
private:
    I_Piece* _piece;     // 操作している駒
    Camera* _mainCamera; // メインカメラ

    I_WorldMat* _startWorldMat; // 初期ワールド行列

    bool _isMoved; // 駒が動いたかどうか確認

    std::unique_ptr<I_SceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<I_SceneState> ExeCancelButton(); // キャンセルボタン処理
    void ExeMouseMove(int xMove, int yMove); // カーソル操作処理

    void MovePieceAndCamera(DirectX::XMFLOAT3 vec); // 駒とカメラを動かす

    MovingPiece(){}

public:
    // 駒操作シーン動作
    std::unique_ptr<I_SceneState> ExeSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    MovingPiece(I_Piece* piece);
    ~MovingPiece();
};