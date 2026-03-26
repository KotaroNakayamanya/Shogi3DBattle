#include"MovingPiece.h"
#include"Application.h"


// 操作開始
ISceneState* MovingPiece::ExeOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    ISceneState* newSceneState = nullptr;

    if(inputMemory & InputHandler::MOUSE_MOVE) // マウス操作処理
    {
        newSceneState = ExeMouseMove(cursorXMove, cursorYMove);
    }
    if(inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        newSceneState = ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        newSceneState = ExeCancelButton();
    if(inputMemory & InputHandler::UP)        // 上ボタン処理
        newSceneState = ExeUpButton();
    if(inputMemory & InputHandler::LEFT)      // 左ボタン処理
        newSceneState = ExeLeftButton();
    if(inputMemory & InputHandler::DOWN)      // 下ボタン処理
        newSceneState = ExeDownButton();
    if(inputMemory & InputHandler::RIGHT)     // 右ボタン処理
        newSceneState = ExeRightButton();

    return newSceneState;
}

// 決定ボタン
ISceneState* MovingPiece::ExeDecisionButton()
{
    return this;
}

// キャンセルボタン処理
ISceneState* MovingPiece::ExeCancelButton()
{
    DestroyWindow(_hwnd);
    return this;
}

// 上ボタン処理
ISceneState* MovingPiece::ExeUpButton()
{
    DirectX::XMFLOAT3 vec = {0, 0.1f, 0};
    MovePieceAndCamera(vec);

    return this;
}

// 左ボタン処理
ISceneState* MovingPiece::ExeLeftButton()
{
    DirectX::XMFLOAT3 vec = {-0.1f, 0, 0};
    MovePieceAndCamera(vec);

    return this;
}

// 下ボタン処理
ISceneState* MovingPiece::ExeDownButton()
{
    DirectX::XMFLOAT3 vec = {0, -0.1f, 0};
    MovePieceAndCamera(vec);

    return this;
}
// 右ボタン処理
ISceneState* MovingPiece::ExeRightButton()
{
    DirectX::XMFLOAT3 vec = {0.1f, 0, 0};
    MovePieceAndCamera(vec);

    return this;
}

// 駒とカメラを動かす
void MovingPiece::MovePieceAndCamera(DirectX::XMFLOAT3 vec)
{
    _piece->Move(vec);
    _camera->MoveCamera(vec);
    _camera->MoveFocus (vec);
}

// マウス移動処理
ISceneState* MovingPiece::ExeMouseMove(int xMove, int yMove)
{
    float fx = xMove / 1000.0f;
    float fy = yMove / 1000.0f;

    _camera->RotationH(fx); // 水平方向にカメラ回転
    _camera->RotationV(fy); // 垂直方向にカメラ回転

    return this;
}




MovingPiece::MovingPiece(Piece* piece)
{
    auto& app = Application::GetInstance();
    auto mainCamera = app.GetMainCamera();

    _piece = piece;
    _camera = mainCamera;
    _hwnd = app.GetHWND();
}

MovingPiece::~MovingPiece(){}