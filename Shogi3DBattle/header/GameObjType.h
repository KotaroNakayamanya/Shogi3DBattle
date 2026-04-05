#pragma once

enum class GameObjType
{
    KING,     // 王
    ROOK,     // 飛車
    BISHOP,   // 角行
    GOLD,     // 金将
    SILVER,   // 銀将
    KNIGHT,   // 桂馬
    LANCE,    // 香車
    PAWN,     // 歩
    BOARD_55, // 5×5将棋盤
    BOARD_99, // 9×9将棋盤
    TYPE_NUM  // 将棋オブジェクト種類数（テクスチャ用意数）
};