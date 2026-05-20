#include"Application.h"

#include<array>
#include<chrono>
#include<thread>

#include"TitleScene.h"

#include"PersProjMat.h"
#include"NonePersProjMat.h"

#include"NewStartButton.h"
#include"ContinueStartButton.h"
#include"OptionButton.h"
#include"ExitGameButton.h"
#include"SelectPieceButton.h"

// 初期処理
void Application::Init()
{   
    _gameObjects->CreateGameObjects(); // ゲームオブジェクト作成
    _textures->CreateTextures();       // テクスチャ作成
    CreateCamera();   // カメラ作成
    InitKeyMap();     // 操作ボタン設定
    InitSceneState(); // シーンステート初期処理

    _gameWindow->InitGameWindow(); // ゲームウインドウ初期処理
    _dx12->InitDX12(); // DirectX12初期処理

    _piecePosManager->InitPiecesPos(); // 駒の位置初期化
}

// カメラ作成
void Application::CreateCamera()
{
    // メインカメラ
    // ビュー行列作成
    auto mainViewMat = std::make_unique<ViewMat>();
    // パースによるプロジェクション行列作成
    auto fov   = DirectX::XM_PIDIV2;
    auto ar    =  16.0f / 9.0f;
    auto nearZ =   1.0f;
    auto farZ  = 150.0f;
    auto mainProjMat = std::make_unique<PersProjMat>(fov, ar, nearZ, farZ);

    _mainCamera = std::make_unique<Camera>(std::move(mainViewMat), std::move(mainProjMat));

    // マップカメラ
    // ビュー行列作成
    auto board = _gameObjects->GetBoard();
    auto boardSize = board->GetBoardSize();
    auto centerPos = boardSize / 2.0f;
    DirectX::XMFLOAT3 eye   = {centerPos, centerPos, -5.0f};
    DirectX::XMFLOAT3 focus = {centerPos, centerPos,  0.0f};
    DirectX::XMFLOAT3 up    = {     0.0f,     -1.0f,  0.0f};
    auto mapViewMat = std::make_unique<ViewMat>(eye, focus, up);
    // パースではないプロジェクション行列作成
    auto margin = 10.0f;
    auto width  = boardSize + margin;
    auto height = boardSize + margin;
         nearZ  =  1.0f;
         farZ   = 10.0f;
    auto mapProjMat = std::make_unique<NonePersProjMat>(width, height, nearZ, farZ);

    _mapCamera = std::make_unique<Camera>(std::move(mapViewMat), std::move(mapProjMat));
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
    _sceneState = std::make_unique<TitleScene>(); // スタート画面
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
            std::unique_ptr<I_SceneState> newSceneState = _sceneState->ExeSceneProcess(
                _inputHandler->GetInputMemory(),
                cursorPos.x,
                cursorPos.y,
                _inputHandler->GetCursorXMove(),
                _inputHandler->GetCursorYMove());
            // シーン更新処理
            if (newSceneState)
            {
                RemoveAllUI();                   // UI削除
                _inputHandler->RemoveLClick();   // 決定ボタン長押し連続押下を回避
                _inputHandler->RemoveRClick();   // キャンセルボタン長押し連続押下を回避
                _sceneState.swap(newSceneState); // シーン更新
            }

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

GameObjects*     Application::GetGameObjects    (){return _gameObjects.get();    } // ゲームオブジェクトを返す
Textures*        Application::GetTextures       (){return _textures.get();       } // テクスチャを返す
DX12*            Application::GetDX12           (){return _dx12.get();           } // DirectX12を返す
GameWindow*      Application::GetGameWindow     (){return _gameWindow.get();     } // ゲームウインドウオブジェクトを返す
InputHandler*    Application::GetInputHandler   (){return _inputHandler.get();   } // インプットハンドラを返す
PiecePosManager* Application::GetPiecePosManager(){return _piecePosManager.get();} // 駒の位置マネージャを返す

Camera* Application::GetMainCamera(){return _mainCamera.get();} // メインカメラを返す
Camera* Application::GetMapCamera() {return _mapCamera.get();}  // マップカメラを返す
KeyMap* Application::GetKeyMap(){return _keyMap.get();} // キー割り当てを返す

void Application::SetIsDrawMap(bool flag){_isDrawMap = flag;} // マップ描画フラグをセット
bool Application::IsDrawMap()            {return _isDrawMap;} // マップ描画フラグを返す


bool Application::IsDrawUINotEmpty(){return _buttonUIs.size() > 0;} // UIの空状況を返す


// UIを全て削除する
void Application::RemoveAllUI()
{
    _frameUIs .clear();
    _textUIs  .clear();
    _buttonUIs.clear();
}

// テキスト枠UIを返す
std::vector<UI*> Application::GetFrameUIs()
{
    std::vector<UI*> vec;
    for(auto& frameUI : _frameUIs) vec.push_back(frameUI.get());
    
    return vec;
}

// テキストUIを返す
std::vector<TextUI*> Application::GetTextUIs()
{
    std::vector<TextUI*> vec;
    for(auto& textUI : _textUIs) vec.push_back(textUI.get());
    
    return vec;
}

// ボタンUIを返す
std::vector<I_Button*> Application::GetButtons()
{
    std::vector<I_Button*> vec;
    for(auto& buttonUI : _buttonUIs) vec.push_back(buttonUI.get());
    
    return vec;
}

// テキストUIをプッシュ
void::Application::PushTextUI(Text2D text2D)
{
    _textUIs.push_back(std::make_unique<TextUI>(text2D));
}

// テキスト付きボタンを作成プッシュ
void Application::PushTextButton(
    TextButtonType textButtonType,
    D2D1_RECT_F    rect)
{
    Text2D text2D;
    text2D.rect = rect;
    text2D.textFormat = GetDX12()->GetNormalTextFormat();
    text2D.brush = GetDX12()->GetBlackBrush();

    std::vector<TextUI*> textUIs;
    
    switch (textButtonType)
    {
        case TextButtonType::NEW_START_BUTTON: // はじめから
            text2D.text = L"はじめから";
            PushTextUI(text2D);
            textUIs.push_back(_textUIs.back().get());
            _buttonUIs.push_back(std::make_unique<NewStartButton>(rect, textUIs));
            break;

        case TextButtonType::CONTINUE_START_BUTTON: // つづきから
            text2D.text = L"つづきから";
            PushTextUI(text2D);
            textUIs.push_back(_textUIs.back().get());
            _buttonUIs.push_back(std::make_unique<ContinueStartButton>(rect, textUIs));
            break;

        case TextButtonType::OPTION_BUTTON: // オプション
            text2D.text = L"オプション";
            PushTextUI(text2D);
            textUIs.push_back(_textUIs.back().get());
            _buttonUIs.push_back(std::make_unique<OptionButton>(rect, textUIs));
            break;

        case TextButtonType::EXIT_GAME_BUTTON: // ゲーム終了
            text2D.text = L"ゲーム終了";
            PushTextUI(text2D);
            textUIs.push_back(_textUIs.back().get());
            _buttonUIs.push_back(std::make_unique<ExitGameButton>(rect, textUIs));
            break;

        default:
            return;
  }

  _frameUIs.push_back(std::make_unique<UI>(rect));
}

// 駒ボタンを作成プッシュ
void Application::PushPieceButton(
    PieceButtonType pieceButtonType,
    D2D1_RECT_F     rect,
    I_Piece*        piece)
{
    switch (pieceButtonType)
    {
        case PieceButtonType::SELECT_PIECE_BUTTON:
            _buttonUIs.push_back(std::make_unique<SelectPieceButton>(rect, piece));
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
    _textures   = std::make_unique<Textures>();
    _dx12 = std::make_unique<DX12>();
    _gameObjects = std::make_unique<GameObjects>();
    _piecePosManager = std::make_unique<PiecePosManager>();

    _keyMap = std::make_unique<KeyMap>();
    _inputHandler = std::make_unique<InputHandler>();
}