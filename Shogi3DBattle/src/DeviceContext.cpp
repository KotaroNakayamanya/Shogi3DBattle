#include"DeviceContext.h"

void DeviceContext::Flash()
{
    _deviceContext->Flush();
}

// デバイスコンテキストセット
void DeviceContext::SetDeviceContext(ComPtr<ID3D11DeviceContext> deviceContext){_deviceContext = deviceContext;}

DeviceContext::DeviceContext(){}
DeviceContext::~DeviceContext(){}