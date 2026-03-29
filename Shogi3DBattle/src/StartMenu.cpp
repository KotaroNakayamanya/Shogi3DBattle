#include"StartMenu.h"
#include"Application.h"
#include"SelectingPiece.h"
//#include"MovingPiece.h"

// スタートメニューシーン動作
ISceneState* StartMenu::ExeSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    static float rotationAngle = 0.01f;

    _mainCamera->RotationH(rotationAngle);

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
    auto& app = Application::GetInstance();
    auto& pieces = app.GetPieces();
    ISceneState* newSceneState = new SelectingPiece();
    //ISceneState* newSceneState = new MovingPiece(pieces[0].get());

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveLClick();

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
        case ShogiObj::BOARD_55:
            focusX = 30.0f;
            focusY = 30.0f;
            break;

        case ShogiObj::BOARD_99:
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

}
StartMenu::~StartMenu(){}