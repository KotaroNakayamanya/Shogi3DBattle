#include"Application.h"

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

    // インプットハンドラ作成(初期は動ける状態）
    _inputHandler = std::make_unique<InputHandler>();

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
     HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // アプリケーションインスタンス取得
    Application& app = Application::GetInstance();
    // インプットハンドラ取得
    InputHandler* inputHandler = app.GetInputHandler();

    switch(msg){

    case WM_GETMINMAXINFO: // ウインドウサイズ制限
    {
        MINMAXINFO *pmmi = (MINMAXINFO *)lParam;
        if (pmmi)
        {
            pmmi->ptMinTrackSize.x = app.GetWindowWidth();
            pmmi->ptMaxTrackSize.x = app.GetWindowWidth();
            pmmi->ptMinTrackSize.y = app.GetWindowHeight();
            pmmi->ptMaxTrackSize.y = app.GetWindowHeight();
        }
        break;
    }


    case WM_LBUTTONDOWN: // 左クリック
        inputHandler->ExeLClick();
        break;

    case WM_RBUTTONDOWN: // 右クリック
        inputHandler->ExeRClick();  
        break;

    case WM_MOUSEMOVE: // マウス移動
        //inputHandler->ExeMouseMove();
        break;

    case WM_CHAR: // キー入力
        inputHandler->ExeInputKey(wParam);
        break;


    case WM_DESTROY: // ウインドウ破棄
        PostQuitMessage(0); // ループ処理終了
        break;


    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}




// 画面サイズ変更処理
void Application::ProcessChangeWindowSize()
{
    // DirectX12オブジェクトへ処理を頼む
    _dx12->ProcessChangeWindowSize(_width, _height);
}

// インプットハンドラを返す
InputHandler* Application::GetInputHandler()
{
    return _inputHandler.get();
}

UINT Application::GetWindowWidth()
{
    return _gameWindow->GetWindowWidth();
}
UINT Application::GetWindowHeight()
{
    return _gameWindow->GetWindowHeight();
}




// シングルトンインスタンスを返す
Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

Application::Application(){}
Application::~Application(){}