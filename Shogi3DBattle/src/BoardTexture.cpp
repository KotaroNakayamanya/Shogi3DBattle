#include"BoardTexture.h"

// 将棋盤テクスチャ作成
void BoardTexture::SetBoardTexture(unsigned int squareNum)
{
    std::vector<Pixel> pixels;

    UINT lineSize = 256;
    UINT width  = lineSize;
    UINT height = lineSize;

    pixels.resize(width * height);

    // 白色でクリア
    for (auto& pixel : pixels)
    {
        pixel.r = 255;
        pixel.g = 255;
        pixel.b = 255;
        pixel.a = 255;
    }

    float squareLength = static_cast<float>(lineSize) / (squareNum + 1);
    float halfSquareLength = squareLength / 2; // マスの半分のサイズ

    UINT drawLowerLimit  = halfSquareLength *  1 + 0.5;
    UINT drawUpperLimit  = halfSquareLength * (1 + squareNum * 2) + 0.5;


    // 黒線を描画する対象座標(x, y)に黒色を格納する
    UINT x = 0;
    UINT y = 0;
    UINT lineNum = squareNum + 1; // 横縦それぞれの線の本数
    for (auto& pixel : pixels)
    {
        // xy座標が横縦それぞれの線の上にあれば黒色を格納
        for (UINT i = 0; i < lineNum; i++)
        {
            // 黒線対象の座標を取得(xとyのどちらにも使える)
            UINT BlackLinePos = halfSquareLength * (1 + i * 2) + 0.5;

            // x座標が黒線の直線上の値であるかチェック
            bool isXOnBlackLine = x == BlackLinePos;
            // y座標が線を描画する範囲にあるかチェック
            bool isYDrawRange = drawLowerLimit <= y && y <= drawUpperLimit;
            // 縦方向の線分上にあれば黒色
            if (isXOnBlackLine && isYDrawRange)
            {
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            }

    
            // y座標が黒線の直線上の値であるかチェック
            bool isYOnBlackLine = y == BlackLinePos;
            // x座標が線を描画する範囲にあるかチェック
            bool isXDrawRange = drawLowerLimit <= x && x <= drawUpperLimit;
            // 横方向の線分上にあれば黒色
            if (isYOnBlackLine && isXDrawRange)
            {
                pixel.r = 0;
                pixel.g = 0;
                pixel.b = 0;
            }
        }

        // xとyの次の座標を取得
        x++;            // xを足す
        if (x >= width) // xが端を超えたらyを足してxを0に戻す
        {
            y++;
            x = 0;
        }
    }

    SetPixels(pixels);
    SetWidth(width);
    SetHeight(height);
}