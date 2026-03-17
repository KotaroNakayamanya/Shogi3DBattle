#include"InputHandler.h"
#include"ISceneState.h"
#include"KeyConf.h"
#include"MovingPiece.h"
#include"Pawn.h"
#include"ViewMat.h"
#include"Application.h"

// 操作開始
void InputHandler::ExeOperation()
{
    ISceneState* newSceneState = nullptr;

    if(_inputMemory & ControllerButton::mouseMove) // マウス操作処理
    {
        newSceneState = _sceneState->ExeMouseMove(_cursorXMove, _cursorYMove);
        _inputMemory ^= ControllerButton::mouseMove; // マウス操作終了は明示する
    }
    if(_inputMemory & ControllerButton::decision)  // 決定ボタン処理
        newSceneState = _sceneState->ExeDecisionButton();
    if(_inputMemory & ControllerButton::cancel)    // キャンセルボタン処理
        newSceneState = _sceneState->ExeCancelButton();
    if(_inputMemory & ControllerButton::up)        // 上ボタン処理
        newSceneState = _sceneState->ExeUpButton();
    if(_inputMemory & ControllerButton::left)      // 左ボタン処理
        newSceneState = _sceneState->ExeLeftButton();
    if(_inputMemory & ControllerButton::down)      // 下ボタン処理
        newSceneState = _sceneState->ExeDownButton();
    if(_inputMemory & ControllerButton::right)     // 右ボタン処理
        newSceneState = _sceneState->ExeRightButton();
    
       
    CheckUpdateSceneState(newSceneState);
}


void InputHandler::MemoryLClick(){_inputMemory |= ControllerButton::decision;} // 左クリック記録
void InputHandler::RemoveLClick(){_inputMemory ^= ControllerButton::decision;} // 左クリック解除
void InputHandler::MemoryRClick(){_inputMemory |= ControllerButton::cancel;} // 右クリック記録
void InputHandler::RemoveRClick(){_inputMemory ^= ControllerButton::cancel;} // 右クリック解除

// キー入力記録
void InputHandler::MemoryInputKey(WPARAM inputKey)
{
    // キーの入力を割り当てられている操作ボタンに変換する
    auto keyConf = _keyConf->convertKeyToControllerButton(inputKey);

    _inputMemory |= keyConf;
}

// キー入力解除
void InputHandler::RemoveInputKey(WPARAM inputKey)
{
    // キーの入力を割り当てられている操作ボタンに変換する
    auto keyConf = _keyConf->convertKeyToControllerButton(inputKey);

    _inputMemory ^= keyConf;
}

// マウス移動処理記録
void InputHandler::MemoryMouseMove(int x, int y)
{
    _cursorXMove = x - _cursorX;
    _cursorYMove = _cursorY - y;

    _cursorX = x;
    _cursorY = y;

    _inputMemory |= ControllerButton::mouseMove;
}
//// マウス移動処理記録
//void InputHandler::MemoryMouseMove(int xMove, int yMove)
//{
//    _cursorXMove = xMove;
//    _cursorYMove = yMove;
//    _inputMemory |= ControllerButton::mouseMove;
//}

void InputHandler::ClearInputMemory(){_inputMemory = 0;} // 入力クリア

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

void InputHandler::SetCursorX(int x){_cursorX = x;}
void InputHandler::SetCursorY(int y){_cursorY = y;}



InputHandler::InputHandler()
{
    Piece*   piece   = Application::GetInstance().GetDX12()->GetPawn();

    _sceneState = std::make_unique<MovingPiece>(piece);
    _keyConf    = std::make_unique<KeyConf>();
}

InputHandler::~InputHandler(){}

