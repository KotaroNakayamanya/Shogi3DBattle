#include"WorldMat.h"
#include<vector>

void              WorldMat::SetMat(DirectX::XMMATRIX mat){_mat = mat;}  // ワールド行列セット
DirectX::XMMATRIX WorldMat::GetMat()                     {return _mat;} // ワールド行列を返す

// バッファに書き込み
HRESULT WorldMat::WriteToBuff(Buff* buff)
{
    DirectX::XMMATRIX* buffMap;

    HRESULT result = buff->GetBuff()->Map(0, nullptr, (void**)&buffMap);
    if (FAILED(result)) return result;

    buffMap += _startDataIdx;

    std::vector<DirectX::XMMATRIX> datas = {GetMat()};

    std::copy(datas.begin(), datas.end(), buffMap);

    buff->GetBuff()->Unmap(0, nullptr);

    return S_OK;
}

unsigned int WorldMat::GetSize()
{
    return 1;
}
