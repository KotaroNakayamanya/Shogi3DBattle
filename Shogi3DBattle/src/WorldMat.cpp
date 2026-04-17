#include"WorldMat.h"
#include<vector>

void              WorldMat::SetMat(DirectX::XMMATRIX mat){_mat = mat;}  // ワールド行列セット
DirectX::XMMATRIX WorldMat::GetMat()                     {return _mat;} // ワールド行列を返す

// バッファに書き込み
void WorldMat::WriteToBuff(ID3D12Resource* buff)
{
    DirectX::XMMATRIX* buffMap;

    HRESULT result;
    result = buff->Map(0, nullptr, (void**)&buffMap);
    assert(SUCCEEDED(result));

    buffMap += _startDataIdx;

    std::vector<DirectX::XMMATRIX> datas = {GetMat()};

    std::copy(datas.begin(), datas.end(), buffMap);

    buff->Unmap(0, nullptr);
}

WorldMat::WorldMat()
{
    _mat = DirectX::XMMatrixIdentity();
}