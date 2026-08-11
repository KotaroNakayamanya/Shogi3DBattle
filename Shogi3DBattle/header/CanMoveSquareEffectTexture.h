#pragma once

#include"I_Texture.h"
#include"I_Piece.h"

class CanMoveSquareEffectTexture : public I_Texture
{
public:
    CanMoveSquareEffectTexture(I_Piece* piece);
};