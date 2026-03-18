#pragma once

#include<d3d12.h>
#include<wrl.h>
#include<memory>
#include<array>
#include"Board.h"
#include"Piece.h"
#include"ViewMat.h"
#include"ProjMat.h"

class ConstBuff
{
    friend class Device; // Direct3Dから参照可能

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<ID3D12Resource> _constBuff; // コンスタントバッファ

public:
    D3D12_GPU_VIRTUAL_ADDRESS GetStartAddress(); // バッファの開始アドレスを返す
    // 変換行列を書き込む
    void WriteToConstBuff(
        Board* board,
        std::array<std::unique_ptr<Piece>, 40>& pieces,
        ViewMat* viewMat,
        ProjMat* projMat);

    ID3D12Resource* GetBuff(); // バッファを返す

    ConstBuff();
    ~ConstBuff();
};