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
        DirectX::XMMATRIX viewProjMat; // ビュープロジェクション行列
        
    }Mat;

    Mat* constBuffMap;
   _constBuff->Map(0, nullptr, (void**)&constBuffMap);
   
   for (auto& piece : pieces)
   {
       constBuffMap->worldMat[piece->GetId()] = piece->GetWorldMat();
   }

   constBuffMap->worldMat[board->GetId()] = board->GetWorldMat();
   constBuffMap->viewProjMat = viewMat->GetViewMat() * projMat->GetProjMat();
   
   

   _constBuff->Unmap(0, nullptr);
}

ID3D12Resource* ConstBuff::GetBuff(){return _constBuff.Get();} // コンスタントバッファを返す

ConstBuff::ConstBuff(){}
ConstBuff::~ConstBuff(){}