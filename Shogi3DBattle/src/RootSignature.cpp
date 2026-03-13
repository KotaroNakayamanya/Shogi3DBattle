#include"RootSignature.h"

ID3D12RootSignature* RootSignature::GetRootSignature(){return _rootSignature.Get();} // ルートシグネチャを返す

RootSignature::RootSignature(){}
RootSignature::~RootSignature(){}