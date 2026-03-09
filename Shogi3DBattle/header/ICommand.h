#pragma once

class ICommand
{
public:
    virtual void Exe() = 0;  // é¿çs
    virtual void Undo() = 0; // é¿çséÊÇËè¡Çµ

    ICommand() = default;
    ~ICommand(){}
};