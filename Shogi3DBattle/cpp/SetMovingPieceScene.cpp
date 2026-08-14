#pragma once

#include"SetMovingPieceScene.h"
#include"Application.h"
#include"RuleManager.h"
#include"SelectingPieceScene.h"
#include"WinningScene.h"

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

    // 駒移動エフェクトを消す
    auto texture = app.GetTextures();
    texture->CreateCanMoveEffectTextures(nullptr);

    // 自分の王が攻撃されているか確認する
    auto playerSide = _piece->GetPlayerSide();
    auto isChecked = RuleManager::GetIsChecked(playerSide);
    app.SetIsPlayerChecked(playerSide, isChecked);

    // 相手の王が攻撃されているか確認する
    auto opponentPlayerSide = playerSide == PlayerSide::PLAYER_1 ?
        PlayerSide::PLAYER_2 : PlayerSide::PLAYER_1;
    isChecked = RuleManager::GetIsChecked(opponentPlayerSide);
    app.SetIsPlayerChecked(opponentPlayerSide, isChecked);

    // 勝利条件を満たしていたら、勝利画面に遷移
    auto isWinning = RuleManager::GetIsWinning(playerSide);
    if(isWinning)
    {
        app.SetIsPlayerWinning(playerSide, isWinning);
        return std::make_unique<WinningScene>(playerSide);
    }
    // 勝利していなければ相手にターンを渡してゲーム続行
    else
    {
        app.SetCurrentPlayerTurn(opponentPlayerSide);
        return std::make_unique<SelectingPieceScene>();
    }

}

SetMovingPieceScene::SetMovingPieceScene(I_Piece* piece, unsigned char row, unsigned char column)
    : _piece(piece), _row(row), _column(column){}