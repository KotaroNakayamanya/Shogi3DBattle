#include"Pawn.h"

Pawn::Pawn()
{
    // 頂点集合作成（駒の大きさを決める）
    CreatePieceVerticesArg arg;

    arg.bottomWidth  = 0.9f; // 底面の横の長さ
    arg.cornerWidth  = 0.7f; // 角部分の横の長さ
    arg.height       = 0.9f; // 高さ
    arg.cornerHeight =       // 角部分の高さ（高さを基準に調整）
        arg.height * 0.7f;
    arg.thickness    = 0.4f; // 駒の厚み

    SetPieceVertices(arg);
}

Pawn::~Pawn(){}