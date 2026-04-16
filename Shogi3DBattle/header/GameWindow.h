#pragma once

#include<Windows.h>

class GameWindow
{
private:
    WNDCLASSEX _windowClass; // ウインドウクラス
    HWND _hwnd; // ウインドウハンドル
    UINT _windowWidth  = 1280; // ウインドウ縦サイズ
    UINT _windowHeight =  720; // ウインドウ横サイズ
    bool _isHiddenCursor; // カーソル表示状況

    void CreateWindowClass(); // ウインドウクラス作成
    void CreateWindowObj();   // ウインドウオブジェクト作成

public:
    void InitGameWindow();  // ゲームウインドウ初期処理

    void DisplayWindow(); // ウインドウを表示する
    void DestroyClass();  // クラス破棄

    void ShowCursor(); // カーソル表示
    void HideCursor(); // カーソルを非表示

    void SetCursorPosCenter(); // カーソルをウインドウ中央にセット

    bool IsHiddenCursor(); // カーソル表示状況
    
    HWND GetHWND(); // ウインドウハンドルを返す
    void SetWindowWidth (UINT windowWidth);  // ウインドウ横サイズセット
    UINT GetWindowWidth();                   // ウインドウ横サイズを返す
    void SetWindowHeight(UINT windowHeight); // ウインドウ縦サイズセット
    UINT GetWindowHeight();                  // ウインドウ縦サイズを返す
};