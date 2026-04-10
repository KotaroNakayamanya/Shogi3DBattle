#pragma once

#include"I_GameObj.h"

class I_Board : public I_GameObj
{
protected:
    std::unique_ptr<Vertices> CreateBoardVertices(float size); // 指定されたサイズの将棋盤頂点集合作成
    
public:
    virtual ~I_Board() = default;
};