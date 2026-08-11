#pragma once

#include"I_SceneState.h"
#include"I_Piece.h"

class SetMovingPieceScene : public I_SceneState
{
private:
    I_Piece*      _piece;  // ‘ÎÛ‚Ì‹î
    unsigned char _row;    // s
    unsigned char _column; // —ñ

public:
    // ‹î‚Ì”z’u“®ìˆ—
    std::unique_ptr<I_SceneState> ExeSceneProcess(
        unsigned char inputMemory,
        int cursorX,
        int cursorY,
        int cursorXMove,
        int cursorYMove) override;

    SetMovingPieceScene(I_Piece* piece, unsigned char row, unsigned char column);
};