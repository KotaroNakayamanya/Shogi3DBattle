#include"I_PieceButton.h"

I_Piece* I_PieceButton::GetPiece(){return _piece;} // ŠÖ˜A•t‚¯‚ç‚ê‚½‹î‚ð•Ô‚·

I_PieceButton::I_PieceButton(D2D1_RECT_F rect, I_Piece* piece)
    : I_Button(rect), _piece(piece){}