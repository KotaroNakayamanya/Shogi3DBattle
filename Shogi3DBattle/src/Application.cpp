#include"Application.h"
#include"cassert"



#include"Pawn.h"




// 初期処理
bool Application::Init()
{
    if(_gameWindow->InitGameWindow() == false) goto failed;    // ゲームウインドウ初期処理
    // 将棋オブジェクト作成
    CreateBoard(BOARD); // 将棋盤作成
    _pieces.resize(40);
    for (int i = 0; i < _pieces.size(); i++)
    {
        _pieces[i] = std::make_unique<Pawn>();
        if(i == 0)
            CreatePiece(_pieces[0].get(), PAWN_1);
        else
            CreatePiece(_pieces[i].get(), PAWN_2);
    }

    if(_dx12->InitDX12(_gameWindow.get()) == false) goto failed; // DirectX12初期処理
    _inputHandler = std::make_unique<InputHandler>(); // インプットハンドラ作成(初期は動ける状態）

    return true;

failed:
    assert(false);
    return false;
}

// 将棋盤作成
void Application::CreateBoard(ShogiObjId id)
{
    _board->SetId(id);

    std::vector<ShogiObj::Vert> vertices;

    vertices =
    {   // 上面図

        // 前面
        {{ 0.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{50.0f,  0.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, UINT(id)}, // 右下
        {{ 0.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, UINT(id)}, // 左上
        {{50.0f, 50.0f, 0.0f},  {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, UINT(id)}, // 右上

        // 背面
        {{ 0.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{50.0f,  0.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右下
        {{ 0.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左上
        {{50.0f, 50.0f, 20.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}  // 右上
    };

    _board->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum BoardVertName // 将棋盤の頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
    };

    indices =
    {
        // 前面
        frontRightBottom, frontLeftBottom,  frontLeftTop,
        frontLeftTop,     frontRightTop,    frontRightBottom,     
        
        // 上側面
        frontRightTop, frontLeftTop, backLeftTop, 
        backLeftTop,   backRightTop, frontRightTop,

        // 右側面
        frontRightBottom, frontRightTop,   backRightTop,
        backRightTop,     backRightBottom, frontRightBottom,

        // 下側面
        frontLeftBottom, frontRightBottom, backRightBottom,
        backRightBottom, backLeftBottom,   frontLeftBottom,

        // 左側面
        frontLeftTop, frontLeftBottom, backLeftBottom,
        backLeftBottom, backLeftTop, frontLeftTop,

        // 背面
        backRightBottom, backLeftBottom, backLeftTop,
        backLeftTop,     backRightTop,   backRightBottom
    };
    _board->SetIndices(indices);
}

// 駒作成
void Application::CreatePiece(Piece* piece, ShogiObjId id)
{
    piece->SetId(id);

    std::vector<ShogiObj::Vert> vertices;

    float bottomWidth  = 0.9f;          // 底面の横の長さ
    float cornerWidth  = 0.7f;          // 角部分の横の長さ
    float height       = 0.9f;          // 高さ
    float cornerHeight = height * 0.7f; // 角部分の高さ（高さを基準に調整）
    float thickness    = 0.4f;          // 駒の厚み

    vertices = // 頂点集合
    {   // 上面図と考えて指定
        // 前面
        {{-bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{ bottomWidth, -height,       -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, UINT(id)}, // 右下
        {{-cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, UINT(id)}, // 左上
        {{ cornerWidth,  cornerHeight, -thickness}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, UINT(id)}, // 右上
        {{ 0.0f,         height,       -thickness}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, UINT(id)}, // 上    

        // 裏面
        {{-bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左下
        {{ bottomWidth, -height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右下
        {{-cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 左上
        {{ cornerWidth,  cornerHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 右上
        {{ 0.0f,         height,       0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, UINT(id)}, // 上
    };

    piece->SetVertices(vertices);


    std::vector<unsigned short> indices;

    enum PieceVertName // 駒の頂点に名前を付ける
    {
        // 前面
        frontLeftBottom,  // 左下
        frontRightBottom, // 右下
        frontLeftTop,     // 左上
        frontRightTop,    // 右上
        frontTop,         // 上

        // 背面
        backLeftBottom,  // 左下
        backRightBottom, // 右下
        backLeftTop,     // 左上
        backRightTop,    // 右上
        backTop          // 上
    };

    indices = // インデックス集合
    {
        // 前面
        frontRightBottom, frontLeftBottom, frontLeftTop,     // 右下　左下　左上
        frontLeftTop,     frontRightTop,   frontRightBottom, // 左上　右上 右下
        frontTop,         frontRightTop,   frontLeftTop,     // 右上　左上　上

        // 裏面
        backLeftBottom,  backRightBottom, backLeftTop, // 左下　右下　左上
        backRightBottom, backRightTop,    backLeftTop, // 右下　右上　左上
        backLeftTop,     backRightTop,    backTop,     // 左上　右上　上

        // 側面上左
        frontTop, frontLeftTop, backLeftTop, // 前面上　前面左上　背面左上
        backTop,  frontTop,     backLeftTop, // 背面上　前面上　　背面左上

        // 側面上右
        backTop,  backRightTop, frontRightTop, // 背面上　背面右上　前面右上
        frontTop, backTop,      frontRightTop, // 前面上　背面上　　前面右上　


        // 側面右
        frontRightBottom, frontRightTop, backRightBottom, // 背面右下　前面右上　背面右下
        frontRightTop,    backRightTop,  backRightBottom, // 背面右上　背面右上　背面右下

        // 側面左
        backLeftBottom, backLeftTop,  frontLeftBottom, // 背面左下　背面左上　前面左下
        backLeftTop,    frontLeftTop, frontLeftBottom, // 背面左上　前面左上　前面左下

        // 底面
        frontLeftBottom, frontRightBottom, backRightBottom, // 前面左下　前面右下　背面右下
        frontLeftBottom, backRightBottom, backLeftBottom    // 前面左下　背面右下　背面左下
    };

    piece->SetIndices(indices);
}

Board* Application::GetBoard(){return _board.get();} // 将棋盤を返す
std::vector<std::unique_ptr<Piece>>& Application::GetPieces(){return _pieces;} // 駒を返す



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
    
    static bool isCursorInited = false; // カーソル位置が画面中央にセットされているか

    static POINT screenLT;
    static POINT screenRB;



    switch(msg){
    case WM_GETMINMAXINFO: // ウインドウサイズ制限
    {
        GameWindow* gameWindow = app.GetGameWindow(); // ゲームウインドウ取得

        RECT windowRect = {0, 0, static_cast<LONG>(gameWindow->GetWindowWidth()), static_cast<LONG>(gameWindow->GetWindowHeight())};
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
        isCursorInited = false; // カーソルが飛んでいる可能性があるためfalseとする
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

        if (isCursorInited)
        {
            UINT x = LOWORD(lParam);   // カーソル動作後の横位置
            UINT y = HIWORD(lParam);   // カーソル動作後の縦位置

            inputHandler->MemoryMouseMove(x, y);

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

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            screenLT = {clientRect.left,  clientRect.top};
            screenRB = {clientRect.right, clientRect.bottom};
            ClientToScreen(hwnd, &screenLT);
            ClientToScreen(hwnd, &screenRB);

            RECT rc;
            SetRect(&rc, screenLT.x, screenLT.y, screenRB.x, screenRB.y);
            ClipCursor(&rc);

            isCursorInited = true; // カーソル中央をtrue
        }
        
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
    _board = std::make_unique<Board>();
    _dx12 = std::make_unique<DX12>();
}
Application::~Application(){}