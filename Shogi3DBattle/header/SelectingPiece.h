#pragma once

#include"ISceneState.h"
#include"Camera.h"
#include"PersProjMat.h"

class SelectingPiece : public ISceneState
{
private:
    Camera*     _mainCamera;       // メインカメラ
    PersProjMat _oldPersProjMat; // プロジェクション行列保存

    std::unique_ptr<ISceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<ISceneState> ExeCancelButton();   // キャンセルボタン処理

    void ReversProjMat(); // パース付きプロジェクション行列に戻す

public:
    // 駒選択シーン動作
    std::unique_ptr<ISceneState> ExeSceneOperation(
        UCHAR inputMemory,
        int cursorX,
        int cursorXMove,
        int cursorY,
        int cursorYMove) override;

    SelectingPiece();
    ~SelectingPiece();
};