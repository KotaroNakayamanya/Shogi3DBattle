#include"GameWindow.h"

// ウィンドウプロシージャ宣言
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// ゲームウインドウ初期処理
bool GameWindow::InitGameWindow()
{
    CreateWindowClass(); // ウインドウクラス作成
    RegisterClassEx(&_windowClass); //ウインドウクラス登録

    RECT windowRect = {0, 0, (LONG)_windowWidth, (LONG)_windowHeight};
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false); // クライアント領域調整

    CreateWindowObj(); // ウインドウオブジェクト作成

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
        _windowClass.lpszClassName, // クラス名
        L"将棋大戦3D",              // ウインドウタイトル
        WS_OVERLAPPEDWINDOW,        // ウインドウスタイル,
        CW_USEDEFAULT,              // 表示x座標
        CW_USEDEFAULT,              // 表示y座標
        _windowWidth,               // ウインドウ幅
        _windowHeight,              // ウインドウ高
        nullptr,                    // 親ウインドウハンドル
        nullptr,                    // メニューハンドル
        _windowClass.hInstance,     // アプリケーションハンドル
        nullptr);                   // 追加パラメータ
}




// ウインドウを表示する
void GameWindow::DisplayWindow()
{
    ShowWindow(_hwnd, SW_SHOW);
}

// クラス破棄
void GameWindow::DestroyClass()
{
    UnregisterClass(_windowClass.lpszClassName, _windowClass.hInstance);
}



// カーソル表示
void GameWindow::ShowCursor()
{
    // 通常のカーソルを表示
    HCURSOR cursor = LoadCursor(nullptr, IDC_ARROW);
    SetCursor(cursor);
    // クリップカーソル解除
    ClipCursor(nullptr);

    _isHiddenCursor = false;
}

// カーソル非表示
void GameWindow::HideCursor()
{
    // カーソルを透明に
    BYTE AND[] = {0};
    BYTE XOR[] = {0};
    HCURSOR cursor;
    cursor = CreateCursor(
        nullptr,
        0, // カーソル横中心点
        0, // カーソル縦中心点
        1, // カーソル横サイズ
        1, // カーソル縦サイズ
        AND,     // AND mask 
        XOR);   // XOR mask );
    SetCursor(cursor);

    // ウインドウのスクリーン座標を取得する
    RECT clientRect;
    GetClientRect(_hwnd, &clientRect);
    POINT screenLT = {clientRect.left,  clientRect.top};
    POINT screenRB = {clientRect.right, clientRect.bottom};
    ClientToScreen(_hwnd, &screenLT);
    ClientToScreen(_hwnd, &screenRB);

    // カーソルをウインドウ内に閉じ込める
    RECT rc;
    SetRect(&rc, screenLT.x, screenLT.y, screenRB.x, screenRB.y);
    ClipCursor(&rc);

    _isHiddenCursor = true;
}

// カーソルをウインドウ中央にセット
void GameWindow::SetCursorPosCenter()
{
    int centerX = _windowWidth  / 2;
    int centerY = _windowHeight / 2;
    POINT center = {centerX, centerY};
    ClientToScreen(_hwnd, &center); // スクリーン座標に変換
    SetCursorPos(center.x, center.y); // カーソルをウインドウ中央にセット
}

bool GameWindow::IsHiddenCursor(){return _isHiddenCursor;}// カーソル表示状況




HWND GameWindow::GetHWND(){return _hwnd;} // ウインドウハンドルを返す 
void GameWindow::SetWindowWidth (UINT windowWidth){_windowWidth = windowWidth;}    // ウインドウ横サイズセット
UINT GameWindow::GetWindowWidth(){return _windowWidth;}                            // ウインドウ横サイズを返す
void GameWindow::SetWindowHeight(UINT windowHeight){_windowHeight = windowHeight;} // ウインドウ縦サイズセット
UINT GameWindow::GetWindowHeight(){return _windowHeight;}                          // ウインドウ縦サイズを返す

GameWindow::GameWindow()
{
    _isHiddenCursor = false;
}
GameWindow::~GameWindow(){}