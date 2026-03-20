#include"ConstBuff.h"

// 変換行列を書き込む
void ConstBuff::WriteToConstBuff(
    Board* board,
    std::array<std::unique_ptr<Piece>, 40>& pieces,
    ViewMat* viewMat,
    ProjMat* projMat)
{
    typedef struct Mat
    {
        DirectX::XMMATRIX worldMat[41]; // ワールド行列(駒 40 将棋盤1）
        DirectX::XMMATRIX viewProjMat;  // ビュープロジェクション行列
        
    }Mat;

    Mat* constBuffMap;
   _buff->Map(0, nullptr, (void**)&constBuffMap);
   
   // 駒ワールド行列
   for (auto& piece : pieces)
   {
       constBuffMap->worldMat[piece->GetId()] = piece->GetWorldMat();
   }

   // 将棋盤ワールド行列
   constBuffMap->worldMat[board->GetId()] = board->GetWorldMat();

   // ビュープロジェクション行列
   constBuffMap->viewProjMat = viewMat->GetViewMat() * projMat->GetProjMat();
   
   _buff->Unmap(0, nullptr);
}

ConstBuff::ConstBuff(){}
ConstBuff::~ConstBuff(){}