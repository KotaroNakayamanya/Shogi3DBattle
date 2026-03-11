#pragma once

class ControllerButton
{
public:
// 2進数の各ビット(0～7ビット）で入力状況を記録（１で入力、0で未入力）
    static enum Button {
        lClick    = 0b1 << 6,
        rClick    = 0b1 << 5,
        mouseMove = 0b1 << 4,
        up        = 0b1 << 3,
        left      = 0b1 << 2,
        down      = 0b1 << 1,
        right     = 0b1 << 0
    };
};