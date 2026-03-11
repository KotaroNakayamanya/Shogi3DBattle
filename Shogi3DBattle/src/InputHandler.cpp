#include"InputHandler.h"
#include"ISceneState.h"
#include"KeyConf.h"
#include"MovingPiece.h"

// 操作開始
void InputHandler::ExeOperation()
{
    ISceneState* newSceneState = nullptr;

    if(_inputMemory & ControllerButton::up)    // 上ボタン処理
        newSceneState = _sceneState->ExeUpButton();
    if(_inputMemory & ControllerButton::left)  // 左ボタン処理
        newSceneState = _sceneState->ExeLeftButton();
    if(_inputMemory & ControllerButton::down)  // 下ボタン処理
        newSceneState = _sceneState->ExeDownButton();
    if(_inputMemory & ControllerButton::right) // 右ボタン処理
        newSceneState = _sceneState->ExeRightButton();

    CheckUpdateSceneState(newSceneState);
        
}

// 左クリック記録
void InputHandler::MemoryLClick()
{
    _inputMemory |= ControllerButton::lClick;
}

// 左クリック解除
void InputHandler::RemoveLClick()
{
    _inputMemory ^= ControllerButton::lClick;
}

// 右クリック記録
void InputHandler::MemoryRClick()
{
    _inputMemory |= ControllerButton::lClick;
}

// 右クリック解除
void InputHandler::RemoveRClick()
{
    _inputMemory ^= ControllerButton::lClick;;
}

// マウス移動処理記録
void InputHandler::MemoryMouseMove()
{
    _inputMemory |= ControllerButton::mouseMove;
}

// 入力クリア
void InputHandler::ClearInputMemory()
{
    _inputMemory = 0;
}

// キー入力記録
void InputHandler::MemoryInputKey(WPARAM inputKey)
{
    // キーの入力を割り当てられている操作ボタンに変換する
    auto keyConf = _keyConf->convertKeyToControllerButton(inputKey);

    _inputMemory |= keyConf;
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
    _keyConf    = std::make_unique<KeyConf>();
}
InputHandler::~InputHandler(){}

InputHandler::InputHandler(Piece* piece) : InputHandler()
{
    _sceneState = std::make_unique<MovingPiece>(piece);
}