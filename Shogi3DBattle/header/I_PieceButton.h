#pragma once

#include"I_Button.h"
#include"I_Piece.h"

class I_PieceButton : public I_Button
{
private:
    I_Piece* _piece; // 関連付けられた駒

protected:
    I_Piece* GetPiece(); // 関連付けられた駒を返す

public:
    I_PieceButton(D2D1_RECT_F rect, I_Piece* piece);
    virtual ~I_PieceButton() = default;
};