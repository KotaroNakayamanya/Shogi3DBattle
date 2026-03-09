#include"InputHandler.h"
#include"ISceneState.h"
#include"KeyConf.h"
#include"MovingPiece.h"

// 左クリック処理
void InputHandler::ExeLClick()
{
    ISceneState* newSceneState;
    newSceneState = _sceneState->ExeDecisionButton(); // 決定ボタン処理

    CheckUpdateSceneState(newSceneState);
}

// 右クリック処理
void InputHandler::ExeRClick()
{
    ISceneState* newSceneState;
    newSceneState = _sceneState->ExeCancelButton(); // キャンセルボタン処理

    CheckUpdateSceneState(newSceneState);
}

// マウス移動処理
void InputHandler::ExeMouseMove()
{
    ISceneState* newSceneState;
    newSceneState = _sceneState->ExeCursorOperation(); // カーソル操作処理

    CheckUpdateSceneState(newSceneState);
}

// キー入力処理
void InputHandler::ExeInputKey(WPARAM inputKey)
{
    // キーの入力を割り当てられている操作ボタンに変換する
    auto keyConf = _keyConf->convertKeyToControllerButton(inputKey);

    ISceneState* newSceneState = nullptr;
    switch (keyConf)
    {
    case ControllerButton::up:
        newSceneState = _sceneState->ExeUpButton();    // 上ボタン処理
        break;

    case ControllerButton::left:
        newSceneState = _sceneState->ExeLeftButton();  // 左ボタン処理
        break;

    case ControllerButton::down:
        newSceneState = _sceneState->ExeDownButton();  // 下ボタン処理
        break;

    case ControllerButton::right:
        newSceneState = _sceneState->ExeRightButton(); // 右ボタン処理
        break;

    default:
        break;
    }

    CheckUpdateSceneState(newSceneState);
}




// シーンステート更新チェック
void InputHandler::CheckUpdateSceneState(ISceneState* sceneState)
{
    // 新しいシーンステートがnullptr以外で、現在と異なれば更新する
    bool isNotNull  = sceneState != nullptr;
    bool isNotEqual = sceneState != _sceneState.get();

    if (isNotNull && isNotEqual) SetSceneState(sceneState);
}

// シーンステート更新
void InputHandler::SetSceneState(ISceneState* sceneState)
{
    _sceneState.reset(sceneState);
}




InputHandler::InputHandler()
{
    _sceneState = std::make_unique<MovingPiece>();
    _keyConf    = std::make_unique<KeyConf>();
}
InputHandler::~InputHandler(){}