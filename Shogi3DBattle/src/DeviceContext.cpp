#include"DeviceContext.h"

void DeviceContext::Flash()
{
    _deviceContext->Flush();
}

DeviceContext::DeviceContext(){}
DeviceContext::~DeviceContext(){}