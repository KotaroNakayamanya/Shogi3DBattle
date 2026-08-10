#pragma once

#include"I_SceneState.h"
#include"I_Piece.h"
#include"Camera.h"

class MovingPieceScene : public I_SceneState
{
private:
    I_Piece* _piece;     // 操作している駒
    Camera* _mainCamera; // メインカメラ
    WorldMat _startWorldMat; // 初期ワールド行列
    bool _isMoved; // 駒が動いたかどうか確認

    std::vector<std::vector<bool>> _canPlaced; // 将棋盤上の移動可能な位置

    unsigned int GetRowFromWorldMat   (WorldMat worldMat); // ワールド行列から行位置を返す
    unsigned int GetColumnFromWorldMat(WorldMat worldMat); // ワールド行列から列位置を返す

    std::unique_ptr<I_SceneState> ExeDecisionButtonProcess(); // 決定ボタン処理
    std::unique_ptr<I_SceneState> ExeCancelButton(); // キャンセルボタン処理
    void ExeMouseMove(int xMove, int yMove); // カーソル操作処理

    void MovePieceAndCamera(DirectX::XMFLOAT3 vec); // 駒とカメラを動かす

public:
    // 駒操作シーン動作
    std::unique_ptr<I_SceneState> ExeSceneProcess(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    MovingPieceScene(I_Piece* piece);
    ~MovingPieceScene();
};