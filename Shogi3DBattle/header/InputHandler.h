#pragma once

typedef unsigned char UCHAR;

class InputHandler
{
public:
    // 2進数の各ビット(0～nビット）で入力状況を記録（１で入力、0で未入力）
    enum Button {
        DECISION   = 0b1 << 6, // 決定
        CANCEL     = 0b1 << 5, // キャンセル
        UP         = 0b1 << 4, // 上
        LEFT       = 0b1 << 3, // 左
        DOWN       = 0b1 << 2, // 下
        RIGHT      = 0b1 << 1, // 右
        MOUSE_MOVE = 0b1 << 0, // カーソル操作
    };

private:
    UCHAR _inputMemory = 0; // 入力記録
    int _cursorX; // カーソルx位置
    int _cursorY; // カーソルy位置
    int _cursorXMove; // カーソルx移動距離
    int _cursorYMove; // カーソルy移動距離

    //void CheckUpdateSceneState(ISceneState* sceneState); // シーンステート更新チェック
    //void SetSceneState(ISceneState* sceneState); // シーンステート更新

public:
    void MemoryLClick(); // 左クリック記録
    void RemoveLClick(); // 左クリック解除
    void MemoryRClick(); // 右クリック記録
    void RemoveRClick(); // 右クリック解除
    void MemoryInputButton(UCHAR button); // ボタン入力記録
    void RemoveInputButton(UCHAR button); // ボタン入力解除
    void MemoryMouseMove(int xMove, int yMove); // マウス移動記録
    void RemoveMouseMove();                     // マウス移動解除
    void ClearInputMemory(); // 入力クリア

    UCHAR GetInputMemory(); // 入力記録を返す
    void SetCursorX(int x); // カーソルx位置セット
    int  GetCursorX();      // カーソルx位置を返す
    void SetCursorY(int y); // カーソルy位置セット
    int  GetCursorY();      // カーソルx位置を返す
    int  GetCursorXMove();      // カーソルx移動距離を返す
    int  GetCursorYMove();      // カーソルy移動距離を返す

    InputHandler();
    ~InputHandler();
};