#pragma once

class ICommand
{
protected:
    ICommand() = default;
public:
    virtual void Exe() = 0;  // é¿çs
    virtual void Undo() = 0; // é¿çséÊÇËè¡Çµ

    ~ICommand(){}
};