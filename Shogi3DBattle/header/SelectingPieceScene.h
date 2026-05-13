#pragma once

#include"I_SelectingButtonScene.h"
#include"I_Piece.h"
#include"Camera.h"
#include"PersProjMat.h"

class SelectingPieceScene : public I_SelectingButtonScene
{
private:
    Camera*     _mainCamera;       // メインカメラ
    PersProjMat _oldPersProjMat; // プロジェクション行列保存
    I_Button* _selectedButton; // 選択されているボタン

    std::unique_ptr<I_SceneState> ExeCancelButton();   // キャンセルボタン処理

    void SetButton() override; // ボタンUIセット

    // 駒選択シーン動作
    std::unique_ptr<I_SceneState> ExeSelectingButtonSceneOperation(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

public:
    SelectingPieceScene();
    ~SelectingPieceScene();
};