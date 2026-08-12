#include"CanMoveSquareEffectTexture.h"
#include"Application.h"
#include"RuleManager.h"

CanMoveSquareEffectTexture::CanMoveSquareEffectTexture(I_Piece* piece)
{
    std::vector<Pixel> pixels;

    // サイズは256*256
    UINT lineSize = 256;
    UINT width    = lineSize;
    UINT height   = lineSize;
    pixels.resize(width * height);

    // 白色でクリア
    for (auto& pixel : pixels)
    {
        pixel.r = 255;
        pixel.g = 255;
        pixel.b = 255;
        pixel.a = 255;
    }

    // マスの長さをピクセルで取得
    auto  board        = Application::GetInstance().GetGameObjects()->GetBoard();
    auto  squareNum    = board->GetBoardSquareNum();
    float squareLength = static_cast<float>(lineSize) / (squareNum + 1);
    float halfSquareLength = squareLength / 2; // マスの半分のサイズ(余白が半分のサイズになっている)

    // それぞれのマス目の位置に処理をする
    if (piece != nullptr)
    {
        // 駒の動ける範囲を取得する
        auto canPlaced = RuleManager::GetCanPlaced(piece);

        unsigned int pixelNum = pixels.size();
        for(int i = 0; i < pixelNum; i++)
        {
            // 対応する行および列の位置を取得する
            unsigned char row = (i / lineSize) < halfSquareLength ?
                0 : ((lineSize - (i / lineSize)) + halfSquareLength) / squareLength;
            unsigned char column = (i % lineSize) < halfSquareLength ?
                0 : ((i % lineSize) + halfSquareLength) / squareLength;

            // マスの位置でなければ何もしない
            if(!RuleManager::GetIsRowAndColumnCorrect(row, column)) continue;

            // 動ける範囲であれば色を付ける
            if (canPlaced[row - 1][column - 1])
            {
                pixels[i].r = 0;
                pixels[i].g = 255;
                pixels[i].b = 0;
            }
        }
    }

    SetPixels(pixels);
    SetWidth(width);
    SetHeight(height);
}
