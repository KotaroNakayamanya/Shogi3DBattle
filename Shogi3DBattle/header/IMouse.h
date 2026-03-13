#pragma once

class IMouse
{
public:
    virtual void Exe(int xMove, int yMove) = 0; // ƒ}ƒEƒX‘€ìˆ—

    IMouse()  = default;
    ~IMouse() = default;
};