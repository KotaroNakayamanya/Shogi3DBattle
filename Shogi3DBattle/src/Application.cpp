#include"Application.h"
#include"DX12.h"
#include<assert.h>

// シングルトンインスタンス
Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

// 初期処理
bool Application::Init()
{
    if(CreateGameWindow() == false) // ゲームウインドウ作成
        return false;

    // DirectX12オブジェクト作成
    _dx12 = std::make_unique<DX12>(_hwnd);
    if(_dx12->CreateDX12Obj() == false)
        return false;

    return true;
}

// 実行処理
void Application::Run()
{
    // ウインドウ表示
    ShowWindow(_hwnd, SW_SHOW);

    MSG msg = {};
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }

        // DirectX12処理
        _dx12->ExeDX12();
    }
}

// 終了処理
void Application::Exit()
{
    UnregisterClass(_windowClass.lpszClassName, _windowClass.hInstance);
}




// ウインドウ作成
bool Application::CreateGameWindow()
{
    CreateWindowClass();
    RegisterClassEx(&_windowClass);
    AdjustWindowRect(&_WINDOW_RECT,
        WS_OVERLAPPEDWINDOW, false);
    CreateWindowObj();

    return true;
}

// ウインドウクラス作成
void Application::CreateWindowClass()
{
    _windowClass.cbSize        = sizeof(WNDCLASSEX);       // サイズ
    _windowClass.lpfnWndProc   = (WNDPROC)WindowProcedure; // プロシージャ
    _windowClass.lpszClassName = _WINDOW_CLASS_NAME;       // クラス名
    _windowClass.hInstance     = GetModuleHandle(nullptr); // アプリケーションハンドル
}

// ウインドウオブジェクト作成
void Application::CreateWindowObj()
{
    _hwnd = CreateWindow(
        _windowClass.lpszClassName,              // クラス名
        _WINDOW_TITLE,                           // ウインドウタイトル
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




// ウインドウプロシージャ
LRESULT WindowProcedure(
     HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}




Application::Application(){}
Application::~Application(){}