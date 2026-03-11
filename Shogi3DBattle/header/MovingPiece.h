#pragma once

#include<memory>
#include"ISceneState.h"
#include"ICommand.h"

#include"Piece.h"

class MovingPiece : public ISceneState
{
private:
    std::unique_ptr<ICommand> _moveForward;
    std::unique_ptr<ICommand> _moveLeft;
    std::unique_ptr<ICommand> _moveBack;
    std::unique_ptr<ICommand> _moveRight;

public:
    ISceneState* ExeDecisionButton() override;  // 決定ボタン処理
    ISceneState* ExeCancelButton()   override;  // キャンセルボタン処理
    ISceneState* ExeCursorOperation() override; // カーソル操作処理

    ISceneState* ExeUpButton()    override; // 上ボタン処理
    ISceneState* ExeLeftButton()  override; // 左ボタン処理
    ISceneState* ExeDownButton()  override; // 下ボタン処理
    ISceneState* ExeRightButton() override; // 右ボタン処理

    MovingPiece(Piece* piece);
    ~MovingPiece();
};