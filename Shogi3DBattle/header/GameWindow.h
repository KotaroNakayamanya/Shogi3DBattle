#pragma once

#include<Windows.h>

class GameWindow
{
private:
    WNDCLASSEX _windowClass; // ウインドウクラス
    HWND       _hwnd; // ウインドウハンドル

    const LONG _WINDOW_WIDTH = 1280;
    const LONG _WINDOW_HIGHT =  720;
    RECT       _WINDOW_RECT  = {0, 0, _WINDOW_WIDTH, _WINDOW_HIGHT};

    void CreateWindowClass(); // ウインドウクラス作成
    void CreateWindowObj();   // ウインドウオブジェクト作成

public:
    bool CreateGameWindow();  // ゲームウインドウ作成
    void DisplayWindow(); // ウインドウを表示する
    void DestroyClass(); // クラス破棄
    HWND GetHWND(); // ウインドウハンドルを返す 

    GameWindow();
    ~GameWindow();
};