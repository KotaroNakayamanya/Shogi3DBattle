#pragma once

#include"I_Texture.h"

class BoardTexture : public I_Texture
{
protected:
    void SetBoardTexture(unsigned int squareNum); // 将棋盤テクスチャ作成
};