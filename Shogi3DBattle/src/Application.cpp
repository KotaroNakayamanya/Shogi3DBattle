#include"Application.h"
#include"cassert"

#include<iostream>

// 初期処理
bool Application::Init()
{
    

    if(_gameWindow->InitGameWindow() == false) goto failed;    // ゲームウインドウ初期処理
    //_gameObj->InitGameObj(); // 将棋盤作成
    if(_dx12->InitDX12(_gameWindow.get()) == false) goto failed; // DirectX12初期処理

    _inputHandler = std::make_unique<InputHandler>(); // インプットハンドラ作成(初期は動ける状態）

    return true;

failed:
    assert(false);
    return false;
}

static int count[16 * 16 * 16 * 16] = {0};

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
        else
        {
            _inputHandler->ExeOperation(); // 操作開始
            _dx12->ExeDX12();
        }

        

        if (msg.message == WM_QUIT)
        {
            break;
        }

        
    }
}

// 終了処理
void Application::Exit()
{
    _gameWindow->DestroyClass();
}




//// 画面サイズ変更処理
//void Application::ProcessChangeWindowSize()
//{
//    // DirectX12オブジェクトへ処理を頼む
//    _dx12->ProcessChangeWindowSize(_gameWindow->GetWindowWidth(), _gameWindow->GetWindowHeight());
//}




// ウインドウプロシージャ
LRESULT CALLBACK WindowProcedure(
     HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application& app = Application::GetInstance(); // アプリケーションインスタンス取得
    InputHandler* inputHandler = app.GetInputHandler(); // インプットハンドラ取得
    
    static bool isCursorPositionedWindowCenter = false; // カーソル位置が画面中央にセットされているか

    static POINT screenLT;
    static POINT screenRB;

    PAINTSTRUCT ps;
    HDC hdc;



    switch(msg){
    case WM_GETMINMAXINFO: // ウインドウサイズ制限
    {
        GameWindow* gameWindow = app.GetGameWindow(); // ゲームウインドウ取得

        RECT windowRect = {0, 0, gameWindow->GetWindowWidth(), gameWindow->GetWindowHeight()};
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
        ClipCursor(nullptr);
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
        //RECT clientRect;
        //GetClientRect(hwnd, &clientRect);


        //int clientCenterXPos = (clientRect.right  - clientRect.left) / 2;
        //int clientCenterYPos = (clientRect.bottom - clientRect.top)  / 2;

        if (isCursorPositionedWindowCenter)
        {
            int x = LOWORD(lParam);   // カーソル動作後の横位置
            int y = HIWORD(lParam);   // カーソル動作後の縦位置

            //int  xMove  = newCursorXPos - clientCenterXPos; // xは元の位置から引いて計算
            //int  yMove  = clientCenterYPos - newCursorYPos; // yは引き算を逆にして、画面上側を正にする

            //int  xMove  = newCursorXPos; // xは元の位置から引いて計算
            //int  yMove  = newCursorYPos; // yは引き算を逆にして、画面上側を正にする

            //bool isMove = (xMove != 0) || (yMove != 0); // カーソルに動きがあったかどうかチェック

            inputHandler->MemoryMouseMove(x, y);
            //bool isMove = (xMove != 0) || (yMove != 0); // カーソルに動きがあったかどうかチェック

            bool isXNearEdge = x < 50 || x > (app.GetWindowWidth()  - 50);
            bool isYNearEdge = y < 50 || y > (app.GetWindowHeight() - 50);

            if (isXNearEdge || isYNearEdge)
            {
                int centerX = app.GetWindowWidth()  / 2;
                int centerY = app.GetWindowHeight() / 2;
                POINT center = {centerX, centerY};
                ClientToScreen(hwnd, &center);
                SetCursorPos(center.x, center.y); // カーソルをウインドウ中央にセット
                inputHandler->SetCursorX(centerX);
                inputHandler->SetCursorY(centerY);
            }



            //if(isMove) // カーソルが動いていたならマウス操作記録
            //    inputHandler->MemoryMouseMove(xMove, yMove);
        }
        else
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
            //RECT clientRect;
            //GetClientRect(hwnd, &clientRect);
            ////POINT screenLT = {clientRect.left, clientRect.top};
            ////POINT screenRB = {clientRect.right, clientRect.bottom};
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            screenLT = {clientRect.left,  clientRect.top};
            screenRB = {clientRect.right, clientRect.bottom};
            ClientToScreen(hwnd, &screenLT);
            ClientToScreen(hwnd, &screenRB);

            RECT rc;
            SetRect(&rc, screenLT.x, screenLT.y, screenRB.x, screenRB.y);
            ClipCursor(&rc);

            isCursorPositionedWindowCenter = true; // カーソル中央をtrue
        }

        //RECT clientRect;
        //GetClientRect(hwnd, &clientRect);
        //int clientCenterXPos = (clientRect.right  - clientRect.left) / 2;
        //int clientCenterYPos = (clientRect.bottom - clientRect.top)  / 2;
        // 
        //POINT centerXY = {clientCenterXPos, clientCenterYPos,};
        //ClientToScreen(hwnd, &centerXY);

        //SetCursorPos(centerXY.x, centerXY.y); // カーソルをウインドウ中央にセット
        //isCursorPositionedWindowCenter = true; // カーソル中央をtrue
        

        // ウインドウの外側にカーソルがあっても無理矢理画面内に入れる
        //POINT nya1 = {clientRect.left, clientRect.top};
        //POINT nya2 = {clientRect.right, clientRect.bottom};
        //ClientToScreen(hwnd, &nya1);
        //ClientToScreen(hwnd, &nya2);
        //RECT rc;
        //SetRect(&rc, nya1.x, nya1.y, nya2.x, nya2.y);
        //ClipCursor(&rc);


        //// カーソルを透明に
        //BYTE AND[] = {0};
        //BYTE XOR[] = {0};
        //HCURSOR cursor;
        //cursor = CreateCursor(
        //     nullptr,
        //     0, // カーソル横中心点
        //     0, // カーソル縦中心点
        //     1, // カーソル横サイズ
        //     1, // カーソル縦サイズ
        //     AND,     // AND mask 
        //     XOR);   // XOR mask );
        //SetCursor(cursor);

        //cursor = LoadCursor(nullptr, IDC_ARROW);
        //SetCursor(cursor);
        
        return 0;
    }
        


    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}




GameWindow* Application::GetGameWindow(){return _gameWindow.get();} // ゲームウインドウオブジェクトを返す
DX12* Application::GetDX12(){return _dx12.get();} // DX12オブジェクトを返す}
InputHandler* Application::GetInputHandler(){return _inputHandler.get();} // インプットハンドラを返す
HWND Application::GetHWND(){return _gameWindow->GetHWND();} // ウインドウハンドルを返す
UINT Application::GetWindowWidth(){return _gameWindow->GetWindowWidth();}   // ウインドウ横サイズを返す
UINT Application::GetWindowHeight(){return _gameWindow->GetWindowHeight();} // ウインドウ縦サイズを返す
ViewMat* Application::GetViewMat(){return _dx12->GetViewMat();} // ビュー行列を返す

// シングルトンインスタンスを返す
Application& Application::GetInstance()
{
    static Application instance;
    return instance;
}

Application::Application()
{
    _gameWindow = std::make_unique<GameWindow>();
    _dx12 = std::make_unique<DX12>();
}
Application::~Application(){}