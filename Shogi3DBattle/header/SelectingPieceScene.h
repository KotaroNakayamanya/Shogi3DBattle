#pragma once

#include"I_SceneState.h"
#include"I_Piece.h"
#include"Camera.h"
#include"PersProjMat.h"

class SelectingPieceScene : public I_SceneState
{
private:
    Camera*     _mainCamera;       // メインカメラ
    PersProjMat _oldPersProjMat; // プロジェクション行列保存
    I_Piece* _selectedPiece; // 選択されている駒

    std::unique_ptr<I_SceneState> ExeDecisionButton(); // 決定ボタン処理
    std::unique_ptr<I_SceneState> ExeCancelButton();   // キャンセルボタン処理

    void ReversProjMat(); // パース付きプロジェクション行列に戻す

public:
    // 駒選択シーン動作
    std::unique_ptr<I_SceneState> ExeSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    SelectingPieceScene();
    ~SelectingPieceScene();
};