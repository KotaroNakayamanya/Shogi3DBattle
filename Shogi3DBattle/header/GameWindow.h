#pragma once

#include<Windows.h>

class GameWindow
{
private:
    WNDCLASSEX _windowClass; // ウインドウクラス
    HWND       _hwnd; // ウインドウハンドル

    UINT _windowWidth  = 1280;
    UINT _windowHeight =  720;
    RECT _windowRect   = {0, 0, (LONG)_windowWidth, (LONG)_windowHeight};

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