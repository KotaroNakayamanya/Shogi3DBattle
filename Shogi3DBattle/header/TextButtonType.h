#pragma once

enum class TextButtonType
{
    NEW_START_BUTTON,          // はじめから
    CONTINUE_START_BUTTON,     // つづきから
    OPTION_BUTTON,             // オプション
    EXIT_GAME_BUTTON,          // ゲーム終了
    SELECT_PIECE_BUTTON,       // 駒選択ボタン（透明）
    BACK_TITLE_BUTTON,         // タイトルに戻るボタン
    PIECE_PROMOTION_BUTTON,    // 駒成りボタン 
    PIECE_NOT_PROMOTION_BUTTON // 駒成らずボタン
};