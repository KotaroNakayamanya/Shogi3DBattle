#include"GameWindow.h"

// ウィンドウプロシージャ宣言
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// ウインドウ作成
bool GameWindow::CreateGameWindow()
{
    CreateWindowClass();
    RegisterClassEx(&_windowClass);
    AdjustWindowRect(&_WINDOW_RECT,
        WS_OVERLAPPEDWINDOW, false);
    CreateWindowObj();

    return true;
}

// ウインドウクラス作成
void GameWindow::CreateWindowClass()
{
    _windowClass.cbSize        = sizeof(WNDCLASSEX);       // サイズ
    _windowClass.lpfnWndProc   = (WNDPROC)WindowProcedure; // プロシージャ
    _windowClass.lpszClassName = L"window";                // クラス名
    _windowClass.hInstance     = GetModuleHandle(nullptr); // アプリケーションハンドル
}

// ウインドウオブジェクト作成
void GameWindow::CreateWindowObj()
{
    _hwnd = CreateWindow(
        _windowClass.lpszClassName,              // クラス名
        L"将棋大戦3D",                           // ウインドウタイトル
        WS_OVERLAPPEDWINDOW,                     // ウインドウスタイル
        CW_USEDEFAULT,                           // 表示x座標
        CW_USEDEFAULT,                           // 表示y座標
        _WINDOW_RECT.right  - _WINDOW_RECT.left, // ウインドウ幅
        _WINDOW_RECT.bottom - _WINDOW_RECT.top,  // ウインドウ高
        nullptr,                                 // 親ウインドウハンドル
        nullptr,                                 // メニューハンドル
        _windowClass.hInstance,                  // アプリケーションハンドル
        nullptr);                                // 追加パラメータ
}

// ウインドウを表示する
void GameWindow::DisplayWindow()
{
    ShowWindow(_hwnd, SW_SHOW);
}

// ウインドウハンドルを返す 
HWND GameWindow::GetHWND()
{
    return _hwnd;
}

// クラス破棄
void GameWindow::DestroyClass()
{
    UnregisterClass(_windowClass.lpszClassName, _windowClass.hInstance);
}

GameWindow::GameWindow(){}
GameWindow::~GameWindow(){}