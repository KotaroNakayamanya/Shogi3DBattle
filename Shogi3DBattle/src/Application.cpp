#include"Application.h"

#include"MovePiece.h"

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

    // キーマップオブジェクト作成
    _keyMap = std::make_unique<KeyMap>();

    // シーンステート作成(初期は動ける状態）
    _sceneState = std::make_unique<MovePiece>(_gameWindow->GetHWND());

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
    Application& app = Application::GetInstance();

    ISceneState* sceneState = app.GetSceneState();
    KeyMap* keyMap = app.GetKeyMapObj();

    ISceneState* newSceneState = nullptr;

    switch(msg){

    case WM_LBUTTONDOWN: // 左クリック（決定）
        newSceneState = sceneState->ExeDecision();
        app.SetSceneState(newSceneState);
        break;

    case WM_RBUTTONDOWN: // 右クリック（キャンセル）
        newSceneState = sceneState->ExeCancel();
        app.SetSceneState(newSceneState);
        break;

    case WM_CHAR: // キーボード入力
        switch (keyMap->convertKeyToDirection(wparam))
        {
        case InputCommand::up: // 上入力
            newSceneState = sceneState->ExeUp();
            break;

        case InputCommand::left: // 左入力
            newSceneState = sceneState->ExeLeft();
            break;

        case InputCommand::down: // 下入力
            newSceneState = sceneState->ExeDown();
            break;

        case InputCommand::right: // 右入力
            newSceneState = sceneState->ExeRight();
            break;

        default:
            break;
        }
        app.SetSceneState(newSceneState);
        break;
    
    case WM_DESTROY: // ウインドウ破棄
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}




// シーンステートを返す
ISceneState* Application::GetSceneState()
{
    return _sceneState.get();
}

// シーンステートをセットする
void Application::SetSceneState(ISceneState* sceneState)
{
    bool isNotEqual = _sceneState.get() != sceneState;
    bool isNotNull  = sceneState != nullptr;

    // 新しいステートならセット
    if(isNotEqual && isNotNull)
        _sceneState.reset(sceneState);
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