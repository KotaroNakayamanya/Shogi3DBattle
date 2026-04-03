#include"StartMenu.h"
#include"Application.h"
#include"SelectingPiece.h"

// スタートメニューシーン動作
ISceneState* StartMenu::ExeSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    // 将棋盤回転
    static float rotationAngle = 0.005f;
    _mainCamera->RotationH(rotationAngle);

    // UI選択チェック
    _selectingUI = UIObj::NONE;
    for (auto& ui : Application::GetInstance().GetUIs())
    {
        auto rect = ui.GetRect();
        bool isCursorInWidthRange  = rect.left <= cursorX && cursorX <= rect.right;
        bool isCursorInHeightRange = rect.top  <= cursorY && cursorY <= rect.bottom;
        bool isSelected = isCursorInWidthRange && isCursorInHeightRange;

        ui.SetIsSelected(isSelected);
        if(isSelected) _selectingUI = ui.GetUIType();

    }

    ISceneState* newSceneState = nullptr;

    if(inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        newSceneState = ExeCancelButton();

    return newSceneState;
}

// 決定ボタン
ISceneState* StartMenu::ExeDecisionButton()
{
    ISceneState* newSceneState;

    switch (_selectingUI)
    {
        case UIObj::NEW_START:
        {
            auto& app = Application::GetInstance();
            newSceneState = new SelectingPiece();
            app.RemoveAllUI();

            auto inputHandler = app.GetInputHandler();
            inputHandler->RemoveLClick();

            break;
        }

        case UIObj::EXIT:
            DestroyWindow(Application::GetInstance().GetGameWindow()->GetHWND());
            newSceneState = this;
            break;

        default:
            newSceneState = this;
            break;
    }

    //if (_selectingUI == UIObj::NEW_START)
    //{
    //    
    //    //auto& pieces = app.GetPieces();
    //    
    //    

    //    

    //    auto inputHandler = Application::GetInstance().GetInputHandler();
    //    inputHandler->RemoveLClick();
    //}
    //else
    //{
    //    newSceneState = this;
    //}
    

    

    return newSceneState;
}

// キャンセルボタン処理
ISceneState* StartMenu::ExeCancelButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());
    return this;
}

StartMenu::StartMenu()
{
    auto& app = Application::GetInstance();

    // メインカメラ調整
    _mainCamera = app.GetMainCamera();
    // フォーカス位置セット
    float focusX, focusY;
    auto board = app.GetBoard();
    switch (board->GetTexId())
    {
        case GameObj::BOARD_55:
            focusX = 30.0f;
            focusY = 30.0f;
            break;

        case GameObj::BOARD_99:
            focusX = 50.0f;
            focusY = 50.0f;
            break;

        default:
            break;
    }
    float focusZ =  0.0f;
    DirectX::XMFLOAT3 focusPos = {focusX, focusY, focusZ};
    _mainCamera->SetFocusPos(focusPos);
    // カメラ位置セット
    float cameraX = focusX - 50.0f;
    float cameraY = focusY - 50.0f;
    float cameraZ = focusZ - 50.0f;
    DirectX::XMFLOAT3 cameraPos = {cameraX, cameraY, cameraZ};
    _mainCamera->SetCameraPos(cameraPos);
    // カメラ上側ベクトルセット
    DirectX::XMFLOAT3 cameraUpVec = {0.0f, 0.0f, -1.0f};
    _mainCamera->SetCameraUpVec(cameraUpVec);

    // UIセット
    auto gameWindow = app.GetGameWindow();
    auto uiWidth = gameWindow->GetWindowWidth() / 3;
    auto uiHeight = gameWindow->GetWindowHeight() / 9;

    float left, top, right, bottom, heightOffset;
    left = (gameWindow->GetWindowWidth() - uiWidth) / 2;
    right = left + uiWidth;
    heightOffset = uiHeight + 3.0f;

    top  = gameWindow->GetWindowHeight() / 2;
    bottom = top + uiHeight;
    app.PushUI(L"はじめから対局", {left, top, right, bottom}, UIObj::NEW_START);

    top    += heightOffset;
    bottom += heightOffset;
    app.PushUI(L"つづきから対局", {left, top, right, bottom}, UIObj::CONTINUE_START);

    top    += heightOffset;
    bottom += heightOffset;
    app.PushUI(L"オプション", {left, top, right, bottom}, UIObj::OPTION);

    top    += heightOffset;
    bottom += heightOffset;
    app.PushUI(L"ゲーム終了", {left, top, right, bottom}, UIObj::EXIT);



    //text = L"aaaaa";
    //rect = {0, 0, 1280, 720};


}
StartMenu::~StartMenu(){}