#include"Application.h"

#include"Pawn.h"
#include<array>
#include"BoardFactory.h"
#include"PieceFactory.h"
#include"BoardVertIndicesFactory.h"
#include"PieceVertIndicesFactory.h"
#include<functional>

// 初期処理
bool Application::Init()
{
    if(_gameWindow->InitGameWindow() == false) goto failed;    // ゲームウインドウ初期処理
    CreateShogiObj(); // 将棋オブジェクト作成

    CreateTex();

    if(_dx12->InitDX12(_gameWindow.get()) == false) goto failed; // DirectX12初期処理
    _inputHandler = std::make_unique<InputHandler>(); // インプットハンドラ作成(初期は動ける状態）

    return true;

failed:
    assert(false);
    return false;
}

// 将棋オブジェクト作成
void Application::CreateShogiObj()
{
    // オブジェクトごとのID格納用
    UINT objId = 0;

    // 将棋オブジェクト作成用関数
    std::function<void(ShogiObj*, ShogiObj::ShogiObjType)> createShogiObjFunction =
        [this, &objId](ShogiObj* shogiObj, ShogiObj::ShogiObjType shogiObjType)
        {
            switch (shogiObjType)
            {
            case ShogiObj::BOARD_55:
                _shogiObjFactory.reset(new BoardFactory());
                break;
            
            case ShogiObj::KING:
            case ShogiObj::ROOK:
            case ShogiObj::BISHOP:
            case ShogiObj::GOLD:
            case ShogiObj::SILVER:
            case ShogiObj::KNIGHT:
            case ShogiObj::LANCE:
            case ShogiObj::PAWN:
                _shogiObjFactory.reset(new PieceFactory());
                break;

            default:
                return;
            }

            _shogiObjFactory->CreateShogiObj(shogiObj, shogiObjType, objId++);
        };

    // 将棋盤作成
    createShogiObjFunction(_board.get(), ShogiObj::BOARD_55);
    // 将棋盤インデックス作成
    _vertIndicesFactory.reset(new BoardVertIndicesFactory());
    _vertIndicesFactory->CreateVertIndices(_boardIndices.get());



    // 駒作成
    UINT kingNum =  2;
    UINT rookNum =  2;
    UINT bishopNum = 2;
    UINT goldNum = 4;
    UINT silverNum = 4;
    UINT knightNum = 4;
    UINT lanceNum = 4;
    UINT pawnNum = 18;

    UINT pieceNum = kingNum
                  + rookNum
                  + bishopNum
                  + goldNum
                  + silverNum
                  + knightNum
                  + lanceNum
                  + pawnNum;

    _pieces.resize(pieceNum);
    for(auto& piece : _pieces) piece = std::make_unique<Piece>();

    for (UINT i = 0; i < kingNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::KING);
    for (UINT i = 0; i < rookNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::ROOK);
    for (UINT i = 0; i < bishopNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::BISHOP);
    for (UINT i = 0; i < goldNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::GOLD);
    for (UINT i = 0; i < silverNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::SILVER);
    for (UINT i = 0; i < knightNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::KNIGHT);
    for (UINT i = 0; i < lanceNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::LANCE);
    for (UINT i = 0; i < pawnNum; i++) createShogiObjFunction(_pieces[objId - 1].get(), ShogiObj::PAWN);

    // 駒の頂点インデックス集合作成
    _vertIndicesFactory.reset(new PieceVertIndicesFactory());
    _vertIndicesFactory->CreateVertIndices(_pieceIndices.get());
    
    // 駒の初期位置調整
    for (int i = 1; i < _pieces.size(); i++)
    {
        _pieces[i]->MoveX(i * 10);
        _pieces[i]->MoveY(10.0f);
    }
}

// テクスチャ作成
void Application::CreateTex()
{
    // 木材テクスチャ作成
    _woodTex = std::make_unique<Tex>();

    std::vector<TexStruct::TexRGBA> woodTex;

    UINT lineSize = 256;
    UINT width  = lineSize;
    UINT height = lineSize;

    woodTex.resize(width * height);

    // 基本色を入れる
    for (auto& rgba : woodTex)
    {
        rgba.r = 226;
        rgba.g = 232;
        rgba.b =  75;
        rgba.a = 255;
    }

    // 板目を入れる
    UINT x = 0;
    UINT y = 0;
    UINT subtColor = 10;
    for (auto& rgba : woodTex)
    {
        if ((x+y) % 20 == 0)
        {
            rgba.r -= subtColor;
            rgba.g -= subtColor;
            rgba.b -= subtColor;

        }

        // xとyの次の座標を取得
        x++;            // xを足す
        if (x >= width) // xが端を超えたらyを足してxを0に戻す
        {
            y++;
            x = 0;
        }
    }

    _woodTex->SetWidth (width);
    _woodTex->SetHeight(height);
    _woodTex->SetTex(woodTex);


    // 将棋盤黒線テクスチャ作成
    _boardLineTex = std::make_unique<Tex>();

    std::vector<TexStruct::TexRGBA> boardLineTex;

    lineSize = 256;
    width  = lineSize;
    height = lineSize;

    boardLineTex.resize(width * height);

    // 白色でクリア
    for (auto& rgba : boardLineTex)
    {
        rgba.r = 255;
        rgba.g = 255;
        rgba.b = 255;
        rgba.a = 255;
    }

    UINT squareNum = 5; // マス数

    float squareLength = static_cast<float>(lineSize) / (squareNum + 1);
    float halfSquareLength = squareLength / 2; // マスの半分のサイズ

    UINT drawLowerLimit  = halfSquareLength *  1 + 0.5;
    UINT drawUpperLimit  = halfSquareLength * (1 + squareNum * 2) + 0.5;

    
    // 黒線を描画する対象座標(x, y)に黒色を格納する
    x = 0;
    y = 0;
    UINT lineNum = squareNum + 1; // 横縦それぞれの線の本数
    for (auto& rgba : boardLineTex)
    {
        // xy座標が横縦それぞれの線の上にあれば黒色を格納
        for (UINT i = 0; i < lineNum; i++)
        {
            // 黒線対象の座標を取得(xとyのどちらにも使える)
            UINT BlackLinePos = halfSquareLength * (1 + i * 2) + 0.5;

            // x座標が黒線の直線上の値であるかチェック
            bool isXOnBlackLine = x == BlackLinePos;
            // y座標が線を描画する範囲にあるかチェック
            bool isYDrawRange = drawLowerLimit <= y && y <= drawUpperLimit;
            // 縦方向の線分上にあれば黒色
            if (isXOnBlackLine && isYDrawRange)
            {
                rgba.r = 0;
                rgba.g = 0;
                rgba.b = 0;
            }

            
            // y座標が黒線の直線上の値であるかチェック
            bool isYOnBlackLine = y == BlackLinePos;
            // x座標が線を描画する範囲にあるかチェック
            bool isXDrawRange = drawLowerLimit <= x && x <= drawUpperLimit;
            // 横方向の線分上にあれば黒色
            if (isYOnBlackLine && isXDrawRange)
            {
                rgba.r = 0;
                rgba.g = 0;
                rgba.b = 0;
            }
        }

        // xとyの次の座標を取得
        x++;            // xを足す
        if (x >= width) // xが端を超えたらyを足してxを0に戻す
        {
            y++;
            x = 0;
        }
    }

    _boardLineTex->SetWidth (width);
    _boardLineTex->SetHeight(height);
    _boardLineTex->SetTex(boardLineTex);
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
Tex* Application::GetWoodTex(){return _woodTex.get();} // テクスチャを返す
Tex* Application::GetBoardLineTex(){return _boardLineTex.get();} // テクスチャを返す
VertIndices* Application::GetBoardVertIndices(){return _boardIndices.get();} // 将棋盤頂点インデックスを返す
VertIndices* Application::GetPieceVertIndices(){return _pieceIndices.get();} // 駒の頂点インデックスを返す

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

    _boardIndices = std::make_unique<VertIndices>();
    _pieceIndices = std::make_unique<VertIndices>();
}
Application::~Application(){}