#pragma once

#include<dwrite.h>
#include<wrl.h>

class DWriteTextFormat
{
    friend class DWriteFactory;

    template<typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
    ComPtr<IDWriteTextFormat> _dWriteTextFormat;

public:
    IDWriteTextFormat* GetDWriteTextFormat(){return _dWriteTextFormat.Get();}

    DWriteTextFormat(){}
    ~DWriteTextFormat(){}
};