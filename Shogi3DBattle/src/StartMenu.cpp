#include"StartMenu.h"
#include"Application.h"
#include"SelectingPiece.h"

#include"NewStartButtonFactory.h"
#include"ContinueStartButtonFactory.h"
#include"OptionButtonFactory.h"
#include"GameExitButtonFactory.h"

// スタートメニューシーン動作
std::unique_ptr<ISceneState> StartMenu::ExeSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    // 将棋盤回転
    static float rotationAngle = 0.005f;
    _mainCamera->RotationH(rotationAngle);

    // ボタンUI選択チェック
    _selectingButtonUI = nullptr;
    auto& buttonUIs = Application::GetInstance().GetButtonUIs();
    for (auto& buttonUI : buttonUIs)
    {
        auto rect = buttonUI->GetRect();
        bool isCursorInWidthRange  = rect.left <= cursorX && cursorX <= rect.right;
        bool isCursorInHeightRange = rect.top  <= cursorY && cursorY <= rect.bottom;
        bool isSelected = isCursorInWidthRange && isCursorInHeightRange;

        buttonUI->SetIsSelected(isSelected);
        if(isSelected) _selectingButtonUI = buttonUI.get();

    }

    std::unique_ptr<ISceneState> newSceneState = nullptr;

    if (inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        newSceneState = ExeCancelButton();

    return newSceneState;
}

// 決定ボタン
std::unique_ptr<ISceneState> StartMenu::ExeDecisionButton()
{
    // ボタンUIが選択されていればボタン処理実行、選択されていなければ何もしない
    return _selectingButtonUI ?
        _selectingButtonUI->ExePushButton() : nullptr;
}

// キャンセルボタン処理
std::unique_ptr<ISceneState> StartMenu::ExeCancelButton()
{
    auto gameWindow = Application::GetInstance().GetGameWindow();
    DestroyWindow(gameWindow->GetHWND());
    return nullptr;
}

StartMenu::StartMenu()
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

    // UIセット
    auto gameWindow = app.GetGameWindow();
    auto uiWidth = gameWindow->GetWindowWidth() / 3;
    auto uiHeight = gameWindow->GetWindowHeight() / 9;

    float left, top, right, bottom, heightOffset;
    left = (gameWindow->GetWindowWidth() - uiWidth) / 2;
    right = left + uiWidth;
    heightOffset = uiHeight + 3.0f;

    D2D1_RECT_F              rect;         // ボタンUI範囲
    std::vector<TextAndRect> textAndRects; // テキスト及びテキスト範囲動的配列
    TextAndRect              textAndRect;  // テキスト及びテキスト範囲

    top  = gameWindow->GetWindowHeight() / 2;
    bottom = top + uiHeight;
    rect = {left, top, right, bottom};
    textAndRect.text = L"はじめから対局";
    textAndRect.rect = {left, top, right, bottom};
    textAndRects.clear();
    textAndRects.push_back(textAndRect);
    app.CreateButtonUI<NewStartButtonFactory>(rect, textAndRects);

    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    textAndRect.text = L"つづきから対局";
    textAndRect.rect = rect;
    textAndRects.clear();
    textAndRects.push_back(textAndRect);
    app.CreateButtonUI<ContinueStartButtonFactory>(rect, textAndRects);

    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    textAndRect.text = L"オプション";
    textAndRect.rect = rect;
    textAndRects.clear();
    textAndRects.push_back(textAndRect);
    app.CreateButtonUI<OptionButtonFactory>(rect, textAndRects);

    rect.top    += heightOffset;
    rect.bottom += heightOffset;
    textAndRect.text = L"ゲーム終了";
    textAndRect.rect = rect;
    textAndRects.clear();
    textAndRects.push_back(textAndRect);
    app.CreateButtonUI<GameExitButtonFactory>(rect, textAndRects);
}
StartMenu::~StartMenu(){}