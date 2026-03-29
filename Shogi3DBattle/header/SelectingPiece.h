#pragma once

#include"ISceneState.h"
#include"Camera.h"
#include"PersProjMat.h"

class SelectingPiece : public ISceneState
{
private:
    Camera*     _mainCamera;       // メインカメラ
    PersProjMat _oldPersProjMat; // プロジェクション行列保存

    ISceneState* ExeDecisionButton(); // 決定ボタン処理
    ISceneState* ExeCancelButton();   // キャンセルボタン処理

    void ReversProjMat(); // パース付きプロジェクション行列に戻す

public:
    // 駒選択シーン動作
    ISceneState* ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    SelectingPiece();
    ~SelectingPiece();
};