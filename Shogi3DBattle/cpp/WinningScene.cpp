#include"WinningScene.h"
#include"Application.h"

// テキストUIセット
void WinningScene::SetTextUI()
{
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    auto dx12 = app.GetDX12();

    auto width      = windowWidth  * 0.8f;
    auto height     = windowHeight * 0.2f;

    auto centerXPos = windowWidth / 2.0f;
    auto left  = centerXPos - (width / 2.0f);
    auto right = left + width;

    auto centerYPos = windowHeight / 2.0f;
    auto top = centerYPos - (height / 2.0f);
    auto bottom = top + height;

    Text2D text2D;
    
    switch (_winningPlayer)
    {
        case PlayerSide::PLAYER_1:
            text2D.text = L"先手の勝利";
            break;
        case PlayerSide::PLAYER_2:
            text2D.text = L"後手の勝利";
            break;
        default:
            break;
    }

    text2D.rect = {left, top, right, bottom};
    text2D.textFormat = dx12->GetTitleFrameTextFormat();
    text2D.brush = dx12->GetBlackBrush();
    app.PushTextUI(text2D);

    auto offset = -5.0f;
    text2D.rect = {left+offset, top+offset, right+offset, bottom+offset};
    text2D.brush = dx12->GetRedBrush();
    app.PushTextUI(text2D);

}

// ボタンセット
void WinningScene::SetButton()
{
    auto& app = Application::GetInstance();

    auto gameWindow   = app.GetGameWindow();
    auto windowWidth  = gameWindow->GetWindowWidth();
    auto windowHeight = gameWindow->GetWindowHeight();

    float height = 60.0f;
    float width  = 280.0f;
    float offset = 50.0f;
    float left   = (windowWidth/2.0f) - (width/2.0f);
    float top    = windowHeight - height - offset;
    float right  = left + width;
    float bottom = top  + height;
    D2D1_RECT_F rect = {left, top, right, bottom};
    app.PushTextButton(TextButtonType::BACK_TITLE_BUTTON, rect);
}

// ボタン選択シーン動作
std::unique_ptr<I_SceneState> WinningScene::ExeSelectingButtonSceneOperation(
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

    std::unique_ptr<I_SceneState> newSceneState = nullptr;

    // 決定ボタン処理
    if (inputMemory & InputHandler::DECISION)
    {
        newSceneState = ExeDecisionButtonProcess();
        // 空でなければゲームを初期化する（その後、タイトルに戻る）
        if (newSceneState != nullptr)
        {
            auto& app = Application::GetInstance();
            app.InitGameState();
        }
    }

    return newSceneState;
}

WinningScene::WinningScene(PlayerSide playerSide) : _winningPlayer(playerSide), _isSetTextUI(false){}