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
    bool isSucceed;

    // ゲームウインドウ作成
    if(CreateGameWindow() == false) return false;

    // DirectX12オブジェクト作成
    _dx12.reset(new DX12(_hwnd));
    if(_dx12->CreateDX12Object() == false) return false;

}

// 実行処理
void Application::Run()
{
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
        _dx12->ExecuteDX12();
    }
}

// 終了処理
void Application::Exit()
{
    ExitGameWindow();
}




// ウインドウ作成
bool Application::CreateGameWindow()
{
    CreateWindowClass();
    RegisterClassEx(&_windowClass);
    AdjustWindowRect(&_WINDOW_RECT,
        WS_OVERLAPPEDWINDOW, false);
    CreateWindowObject();
    ShowWindow(_hwnd, SW_SHOW);

    return true;
}

void Application::CreateWindowClass()
{
    _windowClass.cbSize        = sizeof(WNDCLASSEX);       // サイズ
    _windowClass.lpfnWndProc   = (WNDPROC)WindowProcedure; // プロシージャ
    _windowClass.lpszClassName = _WINDOW_CLASS_NAME;       // クラス名
    _windowClass.hInstance     = GetModuleHandle(nullptr); // アプリケーションハンドル
}

void Application::CreateWindowObject()
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

void Application::ExitGameWindow()
{
    UnregisterClass(_windowClass.lpszClassName, _windowClass.hInstance);
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