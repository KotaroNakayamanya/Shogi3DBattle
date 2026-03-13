#pragma once

class ControllerButton
{
public:
// 2進数の各ビット(0～nビット）で入力状況を記録（１で入力、0で未入力）
    static enum Button {
        decision  = 0b1 << 6, // 決定
        cancel    = 0b1 << 5, // キャンセル
        up        = 0b1 << 4, // 上
        left      = 0b1 << 3, // 左
        down      = 0b1 << 2, // 下
        right     = 0b1 << 1, // 右
        mouseMove = 0b1 << 0, // カーソル操作
    };
};