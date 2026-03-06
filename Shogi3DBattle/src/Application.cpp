#include"Application.h"
#include<assert.h>

#include"GameWindow.h"
#include"DX12.h"
#include"KeyMap.h"

// 初期処理
bool Application::Init()
{
    // ゲームウインドウ作成
    _gameWindow = std::make_unique<GameWindow>();
    if(_gameWindow->CreateGameWindow() == false)
        return false;

    // DirectX12オブジェクト作成
    _dx12 = std::make_unique<DX12>();
    if(_dx12->CreateDX12Obj(_gameWindow->GetHWND()) == false)
        return false;

    // キーマップ作成
    _keyMap = std::make_unique<KeyMap>();

    return true;
}

// 実行処理
void Application::Run()
{
    // ウインドウ表示
    _gameWindow->DisplayWindow();

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
    _gameWindow->DestroyClass();
}




// ウインドウプロシージャ
LRESULT CALLBACK WindowProcedure(
     HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // キーマップを利用する
     KeyMap* keyMap = Application::GetInstance().GetKeyMapObj();

    switch(msg){
    case WM_CHAR:
        switch (keyMap->convertKeyToDirection(wparam))
        {
        case InputCommand::up:
            DestroyWindow(hwnd);
            break;
        case InputCommand::left:
            DestroyWindow(hwnd);
            break;
        case InputCommand::down:
            DestroyWindow(hwnd);
            break;
        case InputCommand::right:
            DestroyWindow(hwnd);
            break;
        default:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}




// キーマップオブジェクトを返す
KeyMap* Application::GetKeyMapObj()
{
    return _keyMap.get();
}




// シングルトンインスタンス
Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

Application::Application(){}
Application::~Application(){}