#include"ReadResourceStates.h"

// ジェネリックリードステートを返す
D3D12_RESOURCE_STATES ReadResourceStates::GetResourceStates()
{
    return D3D12_RESOURCE_STATE_GENERIC_READ;
}