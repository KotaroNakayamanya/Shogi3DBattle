#pragma once

#include"I_PieceFactory.h"
#include"B_GameObjFactory.h"{}

class B_PieceFactory : public I_PieceFactory, public B_GameObjFactory
{
public:
    virtual std::unique_ptr<I_Piece> CreatePiece() = 0; // ãÓçÏê¨
};