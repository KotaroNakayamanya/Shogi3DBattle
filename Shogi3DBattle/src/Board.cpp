#include"Board.h"

// 将棋盤を変更
void Board::ChangeBoard(GameObjType board)
{
    // 将棋盤以外のタイプなどを引数にされていたら何もせずに処理終了
    auto it = _boardSizeMap.find(board);
    if(it == _boardSizeMap.end()) return;

    // サイズ変換のための倍率を取得する
    float currentBoardSize = _boardSizeMap[_gameObjType];
    float afterBoardSize   = _boardSizeMap[board];
    float rate = afterBoardSize / currentBoardSize;

    // ワールド行列変換
    auto mat = _worldMat->GetMat();
    mat *= DirectX::XMMatrixScaling(rate, rate, rate);
    _worldMat->SetWorldMat(mat);
    // 将棋盤タイプ変換
    _gameObjType = board;
    _vertices->SetMulDesignTexId(static_cast<unsigned char>(board));
}