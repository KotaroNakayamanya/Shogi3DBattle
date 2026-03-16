#include"ConstBuff.h"

// バッファの開始アドレスを返す
D3D12_GPU_VIRTUAL_ADDRESS ConstBuff::GetStartAddress()
{
    return _constBuff->GetGPUVirtualAddress();
}

// 変換行列を書き込む
void ConstBuff::WriteToConstBuff(Board* board, Piece* piece, ViewMat* viewMat, ProjMat* projMat)
{
    typedef struct Mat
    {
        DirectX::XMMATRIX boardWorldMat; // 将棋盤ワールド行列
        DirectX::XMMATRIX pieceWorldMat; // 駒ワールド行列
        DirectX::XMMATRIX viewProjMat; // ビュープロジェクション行列
        
    }Mat;

    Mat* constBuffMap;

   _constBuff->Map(0, nullptr, (void**)&constBuffMap);

   constBuffMap->boardWorldMat = board->GetWorldMat();
   constBuffMap->pieceWorldMat = piece->GetWorldMat();
   constBuffMap->viewProjMat = viewMat->GetViewMat() * projMat->GetProjMat();
   
   

   _constBuff->Unmap(0, nullptr);
}
//// 変換行列を書き込む
//void ConstBuff::WriteToConstBuff(ShogiObj* shogiObj, ViewMat* viewMat, ProjMat* projMat)
//{
//    typedef struct Mat
//    {
//        DirectX::XMMATRIX worldMat;    // ワールド行列
//        DirectX::XMMATRIX viewProjMat; // ビュープロジェクション行列
//    }Mat;
//
//    Mat* constBuffMap;
//
//   _constBuff->Map(0, nullptr, (void**)&constBuffMap);
//
//   constBuffMap->worldMat    = shogiObj->GetWorldMat();;
//   constBuffMap->viewProjMat = viewMat->GetViewMat() * projMat->GetProjMat();
//
//   _constBuff->Unmap(0, nullptr);
//}

ID3D12Resource* ConstBuff::GetBuff(){return _constBuff.Get();} // コンスタントバッファを返す

ConstBuff::ConstBuff(){}
ConstBuff::~ConstBuff(){}