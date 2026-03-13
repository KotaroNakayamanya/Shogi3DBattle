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

        _inputHandler->ExeOperation(); // 操作開始
        _dx12->ExeDX12();
    }
}

// 終了処理
void Application::Exit()
{
    _gameWindow->DestroyClass();
}




// 画面サイズ変更処理
void Application::ProcessChangeWindowSize()
{
    // DirectX12オブジェクトへ処理を頼む
    _dx12->ProcessChangeWindowSize(_width, _height);
}

DX12* Application::GetDX12()
{
    return _dx12.get();
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

// ウインドウハンドルを返す
HWND Application::GetHWND()
{
    return _gameWindow->GetHWND();
}


// シングルトンインスタンスを返す
Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

Application::Application(){}
Application::~Application(){}




// ウインドウプロシージャ
LRESULT CALLBACK WindowProcedure(
     HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // アプリケーションインスタンス取得
    Application& app = Application::GetInstance();
    // インプットハンドラ取得
    InputHandler* inputHandler = app.GetInputHandler();



    static bool isCursorPositionedWindowCenter = false; // カーソル位置が画面中央にセットされているか

    switch(msg){

    case WM_GETMINMAXINFO: // ウインドウサイズ制限
    {
        RECT windowRect = {0, 0, app.GetWindowWidth(), app.GetWindowHeight()};
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false); // クライアント領域調整

        UINT windowWidth = windowRect.right - windowRect.left;
        UINT windowHeight = windowRect.bottom - windowRect.top;

        MINMAXINFO *pmmi = (MINMAXINFO *)lParam;
        if (pmmi)
        {
            pmmi->ptMinTrackSize.x = windowWidth;
            pmmi->ptMaxTrackSize.x = windowWidth;
            pmmi->ptMinTrackSize.y = windowHeight;
            pmmi->ptMaxTrackSize.y = windowHeight;
        }
        break;
    }


    case WM_ACTIVATEAPP: // ウインドウアクティブ
        isCursorPositionedWindowCenter = false; // カーソルが飛んでいる可能性があるためfalseとする
        inputHandler->ClearInputMemory();
        return 0;
        

    case WM_LBUTTONDOWN: // 左クリック
        inputHandler->MemoryLClick();
        return 0;

    case WM_LBUTTONUP:   // 左クリック戻り
        inputHandler->RemoveLClick();
        return 0;


    case WM_RBUTTONDOWN: // 右クリック
        inputHandler->MemoryRClick();  
        return 0;

    case WM_RBUTTONUP:   // 右クリック戻り
        inputHandler->RemoveRClick();  
        return 0;

    case WM_KEYDOWN: // キー入力
        inputHandler->MemoryInputKey(wParam);
        return 0;

    case WM_KEYUP: // キーから指を離した
        inputHandler->RemoveInputKey(wParam);
        return 0;

    case WM_DESTROY: // ウインドウ破棄
        PostQuitMessage(0); // ループ処理終了
        break;

    case WM_MOUSEMOVE: // マウス移動
    {
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        int clientCenterXPos = (clientRect.right  - clientRect.left) / 2;
        int clientCenterYPos = (clientRect.bottom - clientRect.top)  / 2;

        if (isCursorPositionedWindowCenter)
        {
            int newCursorXPos = LOWORD(lParam);   // カーソル動作後の横位置
            int newCursorYPos = HIWORD(lParam);   // カーソル動作後の縦位置

            int  xMove  = newCursorXPos - clientCenterXPos; // xは元の位置から引いて計算
            int  yMove  = clientCenterYPos - newCursorYPos; // yは引き算を逆にして、画面上側を正にする
            bool isMove = (xMove != 0) || (yMove != 0); // カーソルに動きがあったかどうかチェック

            if(isMove) // カーソルが動いていたならマウス操作記録
                inputHandler->MemoryMouseMove(xMove, yMove);
        }

        POINT centerXY = {clientCenterXPos, clientCenterYPos,};
        ClientToScreen(hwnd, &centerXY);

        SetCursorPos(centerXY.x, centerXY.y); // カーソルをウインドウ中央にセット
        isCursorPositionedWindowCenter = true; // カーソル中央をtrue


        return 0;
    }

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}