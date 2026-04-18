#include"Application.h"

#include<array>
#include<chrono>
#include<thread>
#include<functional>

#include"TitleMenu.h"

#include"PersProjMat.h"
#include"NonePersProjMat.h"

#include"King.h"
#include"Rook.h"
#include"Bishop.h"
#include"Gold.h"
#include"Silver.h"
#include"Knight.h"
#include"Lance.h"
#include"Pawn.h"


#include"NewStartButton.h"
#include"ContinueStartButton.h"
#include"OptionButton.h"
#include"ExitGameButton.h"

#include"Board9x9.h"

#include"PieceVertIndices.h"
#include"BoardVertIndices.h"
#include"WoodTexture.h"

#include"Board9x9Texture.h"
#include"Board5x5Texture.h"


// 初期処理
void Application::Init()
{   
    CreateGameObj(); // ゲームオブジェクト作成
    CreateTex();      // テクスチャ作成
    CreateCamera();   // カメラ作成
    InitKeyMap();     // 操作ボタン設定
    InitSceneState(); // シーンステート初期処理

    _gameWindow->InitGameWindow();      // ゲームウインドウ初期処理
    _dx12->InitDX12(); // DirectX12初期処理

    // 駒の初期位置調整
    for (int i = 1; i < _pieces.size(); i++)
    {
        DirectX::XMFLOAT3 vec = {i*10.0f, 10.0f, 0.0f};
        _pieces[i]->Move(vec);
    }
}




// ゲームオブジェクト作成
void Application::CreateGameObj()
{
    // 将棋盤作成 
    _board = std::make_unique<Board9x9>();               // 9x9将棋盤作成 
    _boardIndices = std::make_unique<BoardVertIndices>();// 将棋盤インデックス作成

    // 駒作成 
    for (int i = 0; i < 2; i++)  _pieces.push_back(std::make_unique<King>());   // 王作成
    for (int i = 0; i < 2; i++)  _pieces.push_back(std::make_unique<Rook>());   // 飛作成
    for (int i = 0; i < 2; i++)  _pieces.push_back(std::make_unique<Bishop>()); // 角作成
    for (int i = 0; i < 4; i++)  _pieces.push_back(std::make_unique<Gold>());   // 金作成
    for (int i = 0; i < 4; i++)  _pieces.push_back(std::make_unique<Silver>()); // 銀作成
    for (int i = 0; i < 4; i++)  _pieces.push_back(std::make_unique<Knight>()); // 桂作成
    for (int i = 0; i < 4; i++)  _pieces.push_back(std::make_unique<Lance>());  // 香作成
    for (int i = 0; i < 18; i++) _pieces.push_back(std::make_unique<Pawn>());   // 歩作成 
    _pieceIndices = std::make_unique<PieceVertIndices>();                       // 駒の頂点インデックス集合作成
}

// テクスチャ作成
void Application::CreateTex()
{
    // 黄色木材テクスチャ作成
    _woodTexs.push_back(std::make_unique<WoodTexture>());

    // 将棋盤乗算テクスチャ作成
    _boardLineTexs.push_back(std::make_unique<Board5x5Texture>());
    _boardLineTexs.push_back(std::make_unique<Board9x9Texture>());
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
    _sceneState = std::make_unique<TitleMenu>(); // スタート画面
}




// 実行処理
void Application::Run()
{
    // ウインドウ表示
    _gameWindow->DisplayWindow();

    auto framePerS = 120;
    auto msPerFrame = std::chrono::milliseconds(1000 / framePerS);

    MSG msg = {};
    while (true) {
        static auto start = std::chrono::high_resolution_clock::now();

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
            std::unique_ptr<I_SceneState> newSceneState = _sceneState->ExeSceneOperation(
                _inputHandler->GetInputMemory(),
                cursorPos.x,
                cursorPos.y,
                _inputHandler->GetCursorXMove(),
                _inputHandler->GetCursorYMove());
            // シーン更新処理
            if (newSceneState) _sceneState.swap(newSceneState);

            // マウス移動操作を削除
            _inputHandler->RemoveMouseMove();

            // フレーム同期処理
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            auto needSleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(msPerFrame - duration);
            if (needSleepTime.count() > 0) std::this_thread::sleep_for(needSleepTime);
            start = std::chrono::high_resolution_clock::now(); 
            // 描画等実行
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
// 木材テクスチャを返す
std::vector<I_Texture*> Application::GetWoodTexs()
{
    std::vector<I_Texture*> vec;
    for(auto& ele : _woodTexs) vec.push_back(ele.get());

    return vec;
} 
// 将棋盤黒線テクスチャを返す
std::vector<I_Texture*> Application::GetBoardLineTexs()
{
    std::vector<I_Texture*> vec;
    for(auto& ele : _boardLineTexs) vec.push_back(ele.get());

    return vec;
}
NaturalBufferedData<unsigned short>* Application::GetBoardVertIndices(){return _boardIndices.get();} // 駒の頂点インデックスを返す
NaturalBufferedData<unsigned short>* Application::GetPieceVertIndices(){return _pieceIndices.get();} // 駒の頂点インデックスを返す
I_Board* Application::GetBoard(){return _board.get();} // 将棋盤を返す
// 駒を返す
std::vector<I_Piece*> Application::GetPieces()
{
    std::vector<I_Piece*> vec;
    for(auto& ele : _pieces) vec.push_back(ele.get());

    return vec;
} 
KeyMap* Application::GetKeyMap(){return _keyMap.get();} // 将棋盤頂点インデックスを返す

void Application::SetIsDrawMap(bool flag){_isDrawMap = flag;} // マップ描画フラグをセット
bool Application::IsDrawMap()            {return _isDrawMap;} // マップ描画フラグを返す

DX12* Application::GetDX12(){return _dx12.get();} // DirectX12を返す

bool Application::IsDrawUINotEmpty(){return _buttonUIs.size() > 0;} // UIの空状況を返す


// UIを全て削除する
void Application::RemoveAllUI()
{
    _textUIs.clear();
    _buttonUIs.clear();
}

// テキストUIを返す
std::vector<TextUI*> Application::GetTextUIs()
{
    std::vector<TextUI*> vec;
    for(auto& textUI : _textUIs) vec.push_back(textUI.get());
    
    return vec;
}

// ボタンUIを返す
std::vector<I_ButtonUI*> Application::GetButtonUIs()
{
    std::vector<I_ButtonUI*> vec;
    for(auto& buttonUI : _buttonUIs) vec.push_back(buttonUI.get());
    
    return vec;
}

// すべての将棋オブジェクトを返す
std::vector<I_GameObj*> Application::GetGameObjects()
{
    std::vector<I_GameObj*> shogiObjects;

    // 将棋盤を格納
    shogiObjects.push_back(_board.get());
    // 駒を格納
    for(auto& piece : _pieces) shogiObjects.push_back(piece.get());

    return shogiObjects;
}

// すべての頂点インデックスを返す
std::vector<NaturalBufferedData<unsigned short>*> Application::GetAllVertIndices()
{
    std::vector<NaturalBufferedData<unsigned short>*> allVertIndices;

    // 将棋盤を格納
    allVertIndices.push_back(_boardIndices.get());
    // 駒を格納
    allVertIndices.push_back(_pieceIndices.get());

    return allVertIndices;
}
// テキストUIをプッシュ
void::Application::PushTextUI(TextUI textUI)
{
    _textUIs.push_back(std::make_unique<TextUI>(textUI));
}

// ボタンUI作成
void Application::PushButtonUI(
    ButtonUIType        buttonUIType,
    D2D1_RECT_F         rect,
    std::vector<Text2D> text2Ds)
{
    switch (buttonUIType)
    {
        case ButtonUIType::NEW_START_BUTTON: // はじめから
            _buttonUIs.push_back(std::make_unique<NewStartButton>(rect, text2Ds));
            break;

        case ButtonUIType::CONTINUE_START_BUTTON: // つづきから
            _buttonUIs.push_back(std::make_unique<ContinueStartButton>(rect, text2Ds));
            break;

        case ButtonUIType::OPTION_BUTTON: // オプション
            _buttonUIs.push_back(std::make_unique<OptionButton>(rect, text2Ds));
            break;

        case ButtonUIType::EXIT_GAME_BUTTON: // ゲーム終了
            _buttonUIs.push_back(std::make_unique<ExitGameButton>(rect, text2Ds));
            break;

        default:
            return;
  }
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
    _dx12 = std::make_unique<DX12>();

    _keyMap = std::make_unique<KeyMap>();
    _inputHandler = std::make_unique<InputHandler>();

    _mainCamera = std::make_unique<Camera>();
    _mapCamera  = std::make_unique<Camera>();
}