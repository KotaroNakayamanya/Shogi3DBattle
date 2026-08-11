#pragma once

#include"SetMovingPieceScene.h"
#include"Application.h"
#include"RuleManager.h"
#include"SelectingPieceScene.h"

// 駒の配置動作処理
std::unique_ptr<I_SceneState> SetMovingPieceScene::ExeSceneProcess(
    unsigned char inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    // 新しい位置に記録する
    auto& app             = Application::GetInstance();
    auto  piecePosManager = app.GetPiecePosManager();
    piecePosManager->PlacePieceOnBoard(_piece, _row, _column);

    // 自分の王が攻撃されているか確認する
    auto playerSide = _piece->GetPlayerSide();
    auto isChecked = RuleManager::GetIsChecked(playerSide);
    app.SetIsPlayerChecked(playerSide, isChecked);

    // 相手の王が攻撃されているか確認する
    auto opponentPlayerSide = playerSide == PlayerSide::PLAYER_1 ?
        PlayerSide::PLAYER_2 : PlayerSide::PLAYER_1;
    isChecked = RuleManager::GetIsChecked(opponentPlayerSide);
    app.SetIsPlayerChecked(opponentPlayerSide, isChecked);

    // 勝利条件を満たしているかどうか確認する
    auto isWinning = RuleManager::GetIsWinning(playerSide);
    if(isWinning) app.SetIsPlayerWinning(playerSide, isWinning);

    // 勝利していなければ相手にターンを渡してゲーム続行
    app.SetCurrentPlayerTurn(opponentPlayerSide);
    
    return std::make_unique<SelectingPieceScene>();
}

SetMovingPieceScene::SetMovingPieceScene(I_Piece* piece, unsigned char row, unsigned char column)
    : _piece(piece), _row(row), _column(column){}