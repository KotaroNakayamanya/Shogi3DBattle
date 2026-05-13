#include"TitleScene.h"
#include"Application.h"

// テキストUIセット
void TitleScene::SetTextUI()
{
    auto& app = Application::GetInstance();

    auto dx12 = app.GetDX12();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    auto width      = windowWidth  * 0.8f;
    auto height     = windowHeight * 0.2f;

    auto centerXPos = windowWidth / 2;
    auto left  = centerXPos - (width / 2.0f);
    auto right = left + width;

    auto top = windowHeight * 0.1f;
    auto bottom = top + height;


    Text2D text2D;

    text2D.text = L"将棋大戦３D";

    text2D.rect = {left, top, right, bottom};
    text2D.textFormat = dx12->GetTitleFrameTextFormat();
    text2D.brush = dx12->GetBlackBrush();
    app.PushTextUI(text2D);

    auto offset = -5.0f;
    text2D.rect = {left+offset, top+offset, right+offset, bottom+offset};
    text2D.textFormat = dx12->GetTitleTextFormat();
    text2D.brush = dx12->GetYellowBrush();
    app.PushTextUI(text2D);

}

// ボタンUIセット
void TitleScene::SetButton()
{
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    auto uiWidth  = windowWidth  / 3; // UIの横の長さ
    auto uiHeight = windowHeight / 9; // UIの縦の長さ
    
    
    float left = (windowWidth - uiWidth) / 2; // UI左位置　中央揃えのため調整
    float top  = windowHeight / 2;            // UI上位置　真ん中
    float right = left + uiWidth;             // UI右位置　UI左位置に横の長さを足す
    float bottom = top + uiHeight;            // UI下位置　UI上位置に縦の長さを足す

    float heightOffset = uiHeight + 3.0f; // ボタンUIを追加するごとに縦にずらす数値

    D2D1_RECT_F rect; // ボタンUI範囲

    // はじめからボタン
    rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::NEW_START_BUTTON, rect);

    // つづきからボタン
    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    app.PushTextButton(TextButtonType::CONTINUE_START_BUTTON, rect);

    // オプションボタン
    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    app.PushTextButton(TextButtonType::OPTION_BUTTON, rect);

    // ゲーム終了ボタン
    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    app.PushTextButton(TextButtonType::EXIT_GAME_BUTTON, rect);
}

// タイトル画面シーン動作
std::unique_ptr<I_SceneState> TitleScene::ExeSelectingButtonSceneOperation(
    unsigned char inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    // テキストUIセット
    if (!_isSetTextUI)
    {
        SetTextUI();
        _isSetTextUI = true;
    }

    // 将棋盤回転
    static float rotationAngle = 0.005f;
    _mainCamera->RotationH(rotationAngle);

    std::unique_ptr<I_SceneState> newSceneState = nullptr;

    if (inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButtonProcess();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        newSceneState = ExeCancelButton();

    return newSceneState;
}

// キャンセルボタン処理
std::unique_ptr<I_SceneState> TitleScene::ExeCancelButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());
    return nullptr;
}

TitleScene::TitleScene() : _isSetTextUI(false)
{
    auto& app = Application::GetInstance();

    // メインカメラ調整
    _mainCamera = app.GetMainCamera();
    // フォーカス位置セット
    float focusX, focusY;
    auto board = app.GetBoard();
    switch (board->GetGameObjType())
    {
        case GameObjType::BOARD_55:
            focusX = 30.0f;
            focusY = 30.0f;
            break;

        case GameObjType::BOARD_99:
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