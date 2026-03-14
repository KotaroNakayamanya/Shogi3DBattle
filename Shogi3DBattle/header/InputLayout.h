#pragma once

#include<d3d12.h>
#include<vector>

class InputLayout
{
    friend class Device; // Direct3D‚©‚çQÆ‰Â”\

private:
    std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout;

public:
    InputLayout(){}
    ~InputLayout(){}
};