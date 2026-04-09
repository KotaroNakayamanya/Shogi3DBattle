#pragma once

#include"B_GameObjFactory.h"
#include"I_Piece.h"
#include<memory>

class I_PieceFactory : public B_GameObjFactory
{
public:
    virtual std::unique_ptr<I_Piece> CreatePiece() = 0; // ãÓçÏê¨
    
    virtual ~I_PieceFactory() = default;
};