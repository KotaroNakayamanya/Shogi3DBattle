#include"Application.h"

#include<array>
#include"BoardFactory.h"
#include"PieceFactory.h"
#include"BoardVertIndicesFactory.h"
#include"PieceVertIndicesFactory.h"
#include<functional>
#include"StartMenu.h"

#include"PersProjMat.h"
#include"NonePersProjMat.h"

#include"YellowWoodTexFactory.h"

// 初期処理
bool Application::Init()
{   
    CreateShogiObj(); // 将棋オブジェクト作成
    CreateTex();      // テクスチャ作成
    CreateCamera();   // カメラ作成
    InitKeyMap();     // 操作ボタン設定
    InitSceneState(); // シーンステート初期処理

    if(_gameWindow->InitGameWindow() == false) goto failed;      // ゲームウインドウ初期処理
    if(_dx12->InitDX12(_gameWindow.get()) == false) goto failed; // DirectX12初期処理

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
            case ShogiObj::BOARD_99:
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
        DirectX::XMFLOAT3 vec = {i*10.0f, 10.0f, 0.0f};
        _pieces[i]->Move(vec);
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

    //// 黄色木材テクスチャ作成
    //_texFactory.reset(new YellowWoodTexFactory());
    ////_texFactory->CreateTex();

    // 将棋盤黒線テクスチャ作成用関数
    std::function<void(Tex*, ShogiObj::ShogiObjType)> createBoardLineTex =
        [this](Tex* tex, ShogiObj::ShogiObjType shogiObjType)
        {
            std::vector<TexStruct::TexRGBA> boardLineTex;

            UINT lineSize = 256;
            UINT width  = lineSize;
            UINT height = lineSize;

            boardLineTex.resize(width * height);

            // 白色でクリア
            for (auto& rgba : boardLineTex)
            {
                rgba.r = 255;
                rgba.g = 255;
                rgba.b = 255;
                rgba.a = 255;
            }

            UINT squareNum; // マス数

            switch (shogiObjType)
            {
                case ShogiObj::BOARD_55:
                    squareNum = 5;
                    break;

                case ShogiObj::BOARD_99:
                    squareNum = 9;
                    break;

                default:
                    return;
            }

            float squareLength = static_cast<float>(lineSize) / (squareNum + 1);
            float halfSquareLength = squareLength / 2; // マスの半分のサイズ

            UINT drawLowerLimit  = halfSquareLength *  1 + 0.5;
            UINT drawUpperLimit  = halfSquareLength * (1 + squareNum * 2) + 0.5;

    
            // 黒線を描画する対象座標(x, y)に黒色を格納する
            UINT x = 0;
            UINT y = 0;
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

            tex->SetWidth (width);
            tex->SetHeight(height);
            tex->SetTex(boardLineTex);
        };

    INT boardTexNum = 2;
    _boardLineTexs.resize(boardTexNum);

    std::vector<ShogiObj::ShogiObjType> boardType =
    {
        ShogiObj::BOARD_55,
        ShogiObj::BOARD_99
    };
    _boardLineTexs.resize(boardType.size());
    
    
    for(UINT i = 0; i < _boardLineTexs.size(); i++)
    {
        auto& boardLineTex = _boardLineTexs[i];
        auto& type         = boardType[i];

        boardLineTex = std::make_unique<Tex>();
        createBoardLineTex(boardLineTex.get(), type);
    }

    
}

// カメラ作成
void Application::CreateCamera()
{
    // メインカメラ
    // ビュー行列作成
    ViewMat* mainViewMat;
    mainViewMat = new ViewMat();
    DirectX::XMFLOAT3 f;
    _mainCamera->SetViewMat(mainViewMat);
    // パースによるプロジェクション行列作成
    PersProjMat* mainProjMat;
    mainProjMat = new PersProjMat();
    mainProjMat->SetFOV  (DirectX::XM_PIDIV2);
    mainProjMat->SetAR   (16.0f / 9.0f);
    mainProjMat->SetNearZ(1.0f);
    mainProjMat->SetFarZ (150.0f);
    _mainCamera->SetProjMat(mainProjMat);

    // マップカメラ
    // ビュー行列作成
    ViewMat* mapViewMat;
    mapViewMat = new ViewMat();
    f = {30.0f, 30.0f, -30.0f}; mapViewMat->SetEye  (f);
    f = {30.0f, 30.0f,   0.0f}; mapViewMat->SetFocus(f);
    f = {0.0f,   1.0f,   0.0f}; mapViewMat->SetUp   (f);
    _mapCamera->SetViewMat(mapViewMat);
    // パースではないプロジェクション行列作成
    NonePersProjMat* mapProjMat;
    mapProjMat = new NonePersProjMat();
    mapProjMat->SetWidth (70.0f);
    mapProjMat->SetHeight(70.0f);
    mapProjMat->SetNearZ(0.0f);
    mapProjMat->SetFarZ (50.0f);
    _mapCamera->SetProjMat(mapProjMat);

}

// 操作ボタン初期処理
void Application::InitKeyMap()
{
    _keyMap->RegisterKeyMap('W', InputHandler::UP);    // w　→　上ボタン
    _keyMap->RegisterKeyMap('A', InputHandler::LEFT);  // a　→　左ボタン
    _keyMap->RegisterKeyMap('S', InputHandler::DOWN);  // s　→　下ボタン
    _keyMap->RegisterKeyMap('D', InputHandler::RIGHT); // d　→　右ボタン
}

// シーンステート初期処理
void Application::InitSceneState()
{
    _sceneState = std::make_unique<StartMenu>(); // スタート画面
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
        else
        {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(_gameWindow->GetHWND(), &cursorPos);
            // シーン動作
            ISceneState* newSceneState = _sceneState->ExeSceneOperation(
                _inputHandler->GetInputMemory(),
                cursorPos.x,
                _inputHandler->GetCursorXMove(),
                cursorPos.y,
                _inputHandler->GetCursorYMove());
            // シーン更新チェック
            CheckUpdateScene(newSceneState);
            // マウス移動操作を削除
            _inputHandler->RemoveMouseMove();
            // 描画等実行
            _dx12->ExeDX12();
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }

        
    }
}

// シーン更新チェック
void Application::CheckUpdateScene(ISceneState* sceneState)
{
    bool isNotNullPtr    = sceneState != nullptr;
    bool isNotEqualScene = sceneState != _sceneState.get();

    // シーンがnullではなく、現在以外のシーンであれば更新
    if(isNotNullPtr && isNotEqualScene) _sceneState.reset(sceneState);
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
    auto inputHandler = Application::GetInstance().GetInputHandler(); // インプットハンドラ取得
    static bool isCursorNotInited = true; // カーソル位置が画面中央にセットされているか


    switch(msg){
        case WM_GETMINMAXINFO: // ウインドウサイズ制限
        {
            auto gameWindow = Application::GetInstance().GetGameWindow(); // ゲームウインドウ取得

            RECT windowRect = // ウインドウサイズを定義
            {
                0,
                0,
                static_cast<LONG>(gameWindow->GetWindowWidth()),
                static_cast<LONG>(gameWindow->GetWindowHeight())
            };
            AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false); // クライアント領域のサイズになるように調整

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
            isCursorNotInited = true; // カーソルが飛んでいる可能性があるため初期化が必要
            inputHandler->ClearInputMemory();
            break;
        
        case WM_LBUTTONDOWN: // 左クリック
            inputHandler->MemoryLClick();
            break;
        case WM_LBUTTONUP: // 左クリック離し
            inputHandler->RemoveLClick();
            break;

        case WM_RBUTTONDOWN: // 右クリック
            inputHandler->MemoryRClick();  
            break;
        case WM_RBUTTONUP: // 右クリック離し
            inputHandler->RemoveRClick();  
            break;

        case WM_KEYDOWN: // キー入力
        {
            auto keyMap = Application::GetInstance().GetKeyMap(); // キーマップ取得
            inputHandler->MemoryInputButton(keyMap->ConvertKeyToButton(wParam));
            break;
        }
        case WM_KEYUP: // キーから指を離した
        {
            auto keyMap = Application::GetInstance().GetKeyMap(); // キーマップ取得
            inputHandler->RemoveInputButton(keyMap->ConvertKeyToButton(wParam));
            break;
        }
        

        case WM_MOUSEMOVE: // マウス移動
        {
            UINT x = LOWORD(lParam);   // カーソル動作後の横位置
            UINT y = HIWORD(lParam);   // カーソル動作後の縦位置

            if (isCursorNotInited) // 初期化する
            {
                inputHandler->SetCursorX(x);
                inputHandler->SetCursorY(y);
                isCursorNotInited = false; // カーソル初期済みをtrue
               
            }
            else // 初期化されていれば処理
            {
                inputHandler->MemoryMouseMove(x, y); // カーソル位置から移動量も記録

                auto gameWindow = Application::GetInstance().GetGameWindow(); // ゲームウインドウ取得
                // カーソル非表示の処理であれば、ウインドウ領域内にカーソルを閉じ込める処理をする
                if (gameWindow->IsHiddenCursor())
                {
                    UINT windowWidth  = gameWindow->GetWindowWidth();  // ウインドウ横サイズ
                    UINT windowHeight = gameWindow->GetWindowHeight(); // ウインドウ縦サイズ
                    UINT edgeRange    = 50;                            // 端サイズ   

                    bool isXNearEdge = edgeRange < x || x > (windowWidth  - edgeRange);
                    bool isYNearEdge = edgeRange < y || y > (windowHeight - edgeRange);
                    
                    // カーソル位置がウインドウの端にいたら、中央に戻す
                    if (isXNearEdge || isYNearEdge)
                    {
                        gameWindow->SetCursorPosCenter(); // カーソルをウインドウ中央へ
                        inputHandler->SetCursorX(windowWidth  / 2); // カーソル横位置記録
                        inputHandler->SetCursorY(windowHeight / 2); // カーソル縦位置記録
                    }
                }
            }

            break;
        }

        case WM_DESTROY: // ウインドウ破棄
            PostQuitMessage(0); // ループ処理終了
            break;

        default:
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


GameWindow* Application::GetGameWindow(){return _gameWindow.get();} // ゲームウインドウオブジェクトを返す
InputHandler* Application::GetInputHandler(){return _inputHandler.get();} // インプットハンドラを返す

Camera* Application::GetMainCamera(){return _mainCamera.get();} // メインカメラを返す
Camera* Application::GetMapCamera() {return _mapCamera.get();}  // マップカメラを返す

Tex* Application::GetWoodTex(){return _woodTex.get();} // 木材テクスチャを返す
//Tex* Application::GetBoardLineTex(){return _boardLineTex.get();} // 将棋盤黒線テクスチャを返す
std::vector<std::unique_ptr<Tex>>& Application::GetBoardLineTexs(){return _boardLineTexs;} // 将棋盤黒線テクスチャを返す
VertIndices* Application::GetBoardVertIndices(){return _boardIndices.get();} // 将棋盤頂点インデックスを返す
VertIndices* Application::GetPieceVertIndices(){return _pieceIndices.get();} // 駒の頂点インデックスを返す
Board* Application::GetBoard(){return _board.get();} // 将棋盤を返す
std::vector<std::unique_ptr<Piece>>& Application::GetPieces(){return _pieces;} // 駒を返す
KeyMap* Application::GetKeyMap(){return _keyMap.get();} // 将棋盤頂点インデックスを返す

void Application::SetIsDrawMap(bool flag){_isDrawMap = flag;} // マップ描画フラグをセット
bool Application::IsDrawMap()            {return _isDrawMap;} // マップ描画フラグを返す

bool Application::IsDrawUINotEmpty(){return _uis.size() > 0;} // UIの空状況を返す
void Application::PushUI(std::wstring text, D2D1_RECT_F rect, UIObj::UIType uiType)
{
    //UIObj ui = {L"aaa", {0, 0, 1280, 720}};
    //_uis.push_back(ui);
    _uis.push_back({text, rect, uiType});

//_uis.push_back(ui);
}   // UIをプッシュする
void Application::RemoveAllUI(){_uis.clear();}      // UIを全て削除する
std::vector<UIObj>& Application::GetUIs(){return _uis;} // UIを返す

// すべての将棋オブジェクトを返す
std::vector<ShogiObj*> Application::GetShogiObjects()
{
    std::vector<ShogiObj*> shogiObjects;

    // 将棋盤を格納
    shogiObjects.push_back(_board.get());
    // 駒を格納
    for(auto& piece : _pieces) shogiObjects.push_back(piece.get());

    return shogiObjects;
}

// すべての頂点インデックスを返す
std::vector<VertIndices*> Application::GetAllVertIndices()
{
    std::vector<VertIndices*> allVertIndices;

    // 将棋盤を格納
    allVertIndices.push_back(_boardIndices.get());
    // 駒を格納
    allVertIndices.push_back(_pieceIndices.get());

    return allVertIndices;
}




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

    _keyMap = std::make_unique<KeyMap>();
    _inputHandler = std::make_unique<InputHandler>();

    _mainCamera = std::make_unique<Camera>();
    _mapCamera  = std::make_unique<Camera>();
}