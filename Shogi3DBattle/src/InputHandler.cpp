#include"InputHandler.h"
#include"KeyMap.h"

void InputHandler::MemoryLClick()                 {_inputMemory |=  DECISION;} // 左クリック記録
void InputHandler::RemoveLClick()                 {_inputMemory &= ~DECISION;} // 左クリック解除
void InputHandler::MemoryRClick()                 {_inputMemory |=  CANCEL;}   // 右クリック記録
void InputHandler::RemoveRClick()                 {_inputMemory &= ~CANCEL;}   // 右クリック解除
void InputHandler::MemoryInputButton(UCHAR button){_inputMemory |=  button;}           // キー入力記録
void InputHandler::RemoveInputButton(UCHAR button){_inputMemory &= ~button;}           // キー入力解除
// マウス移動処理記録
void InputHandler::MemoryMouseMove(int x, int y)
{
    // 右と上を正としてマウス動作距離を保存
    _cursorXMove = x - _cursorX;
    _cursorYMove = _cursorY - y;

    // 現在のマウス位置を保存
    _cursorX = x;
    _cursorY = y;

    _inputMemory |= MOUSE_MOVE;
}
void InputHandler::RemoveMouseMove(){_inputMemory &= ~MOUSE_MOVE;} // マウス移動解除


void InputHandler::ClearInputMemory(){_inputMemory = 0;} // 入力クリア


UCHAR InputHandler::GetInputMemory(){return _inputMemory;} // 入力記録を返す
void InputHandler::SetCursorX(int x){_cursorX = x;}    // カーソルx位置セット
int  InputHandler::GetCursorX()     {return _cursorX;} // カーソルx位置を返す
void InputHandler::SetCursorY(int y){_cursorY = y;}    // カーソルy位置セット
int  InputHandler::GetCursorY()     {return _cursorY;} // カーソルy位置を返す
int  InputHandler::GetCursorXMove() {return _cursorXMove;} // カーソルx移動距離を返す
int  InputHandler::GetCursorYMove() {return _cursorYMove;} // カーソルy移動距離を返す


InputHandler::InputHandler(){}
InputHandler::~InputHandler(){}

