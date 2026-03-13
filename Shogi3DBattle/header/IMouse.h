#pragma once

class IMouse
{
public:
    virtual void Exe(int xMove, int yMove) = 0;

    IMouse()  = default;
    ~IMouse() = default;
};