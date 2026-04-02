#include"MovingPiece.h"
#include"Application.h"
//#include"StartMenu.h"
#include"SelectingPiece.h"
#include<cmath>

// 駒操作シーン動作
ISceneState* MovingPiece::ExeSceneOperation(
    UCHAR inputMemory,
    int cursorX,
    int cursorXMove,
    int cursorY,
    int cursorYMove)
{
    ISceneState* newSceneState = nullptr;

    if(inputMemory & InputHandler::MOUSE_MOVE) // マウス操作処理
        ExeMouseMove(cursorXMove, cursorYMove);

    float moveX = 0.0f, moveY = 0.0f;
    if(inputMemory & InputHandler::RIGHT) moveX += 1.0f;
    if(inputMemory & InputHandler::LEFT)  moveX -= 1.0f;
    if(inputMemory & InputHandler::UP)    moveY += 1.0f;
    if(inputMemory & InputHandler::DOWN)  moveY -= 1.0f;

    if (moveX != 0.0f || moveY != 0.0f)
    {
        DirectX::XMFLOAT3 moveXYVec = {moveX, moveY, 0};
        auto normMoveXYVec = VecCalc::GetNormFloat(moveXYVec);

        // z方向を0にし、正規化された視線ベクトルを取得
        auto lookVec_z0 = _mainCamera->GetNormLookVec();
        lookVec_z0.z = 0;
        auto normLookVec_z0 = VecCalc::GetNormFloat(lookVec_z0);

        // normLookVec_z0.yの値は(0,1,0)との内積の結果になる
        // 正規化したもの同士の内積のため、cosθの値である
        auto cos = normLookVec_z0.y;

        // normLookVec_z0.xの符号が負ならθは正方向、正ならθは負方向
        auto theta = normLookVec_z0.x < 0 ?
            std::acos(cos) : -std::acos(cos);

        // θ分だけZ軸を中心に回転する行列を作る
        auto rotationZ = DirectX::XMMatrixRotationZ(theta);

        // xy座標での動きをカメラを正面とした動きに変換
        auto normMoveVec = VecCalc::GetFloat3MulMat(normMoveXYVec, rotationZ);

        // 駒とカメラを動かす
        MovePieceAndCamera(normMoveVec);
    }

    if(inputMemory & InputHandler::DECISION)  // 決定ボタン処理
        return ExeDecisionButton();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        return ExeCancelButton();


    

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
    ISceneState* newSceneState;
    if (_isMoved) // 駒を動かしていたら駒を初期位置に戻し、カメラとフォーカスを平行移動する
    {
        // 元の位置に動かすまでのベクトルを取得
        auto subtMat = _startWorldMat - _piece->GetMat();
        auto subtFloat4x4 = VecCalc::GetFoloat4x4FromMat(subtMat);
        auto vecX = subtFloat4x4._41;
        auto vecY = subtFloat4x4._42;
        auto vecZ = 0.0f;
        DirectX::XMFLOAT3 moveVec = {vecX, vecY, vecZ};

        // 駒のワールド行列を初期化、カメラを平行移動
        _piece->SetWorldMat(_startWorldMat);
        _mainCamera->MoveCameraPos(moveVec);
        _mainCamera->MoveFocusPos (moveVec);

        // 駒は動いてない状態に
        _isMoved = false;
        newSceneState = this;
    }   
    else          // 駒を動かしていなければメニュー画面に戻す
    {
        // カーソル表示
        auto& app = Application::GetInstance();
        auto gameWindow = app.GetGameWindow();
        gameWindow->ShowCursor();

        // マップ描画フラグを解除
        Application::GetInstance().SetIsDrawMap(false); 
        
        // シーンを駒選択シーンに変更
        newSceneState = new SelectingPiece();
    }

    auto inputHandler = Application::GetInstance().GetInputHandler();
    inputHandler->RemoveRClick();
        
    return newSceneState;
}

// 駒とカメラを動かす
void MovingPiece::MovePieceAndCamera(DirectX::XMFLOAT3 vec)
{
    _piece->Move(vec);
    _mainCamera->MoveCameraPos(vec);
    _mainCamera->MoveFocusPos (vec);
    _isMoved = true;
}

// マウス移動処理
void MovingPiece::ExeMouseMove(int xMove, int yMove)
{
    float fx = xMove / 1000.0f;
    float fy = yMove / 1000.0f;

    _mainCamera->RotationH(fx); // 水平方向にカメラ回転
    _mainCamera->RotationV(fy); // 垂直方向にカメラ回転
}





MovingPiece::MovingPiece(Piece* piece)
{
    _piece = piece; // 操作対象の駒を取得
    _mainCamera = Application::GetInstance().GetMainCamera(); // メインカメラ取得
    
    auto worldMat = piece->GetMat(); // 駒のワールド行列取得
    _startWorldMat = worldMat; // ワールド行列初期値として取得しておく
    
    
    // カメラのフォーカス位置を駒の位置を基準にセット
    auto worldFloat4x4 = VecCalc::GetFoloat4x4FromMat(worldMat);
    auto focusX = worldFloat4x4._41;
    auto focusY = worldFloat4x4._42;
    auto focusZ = worldFloat4x4._43 - 8.0f;
    DirectX::XMFLOAT3 focusPos = {focusX, focusY, focusZ};
    _mainCamera->SetFocusPos(focusPos);

    // カメラの位置をフォーカス位置に合わせてセット
    DirectX::XMFLOAT3 cameraPos = {focusX, focusY - 10.0f, focusZ - 10.0f};
    _mainCamera->SetCameraPos(cameraPos);

    // カメラ上側ベクトルセット
    DirectX::XMFLOAT3 cameraUpVec = {0.0f, 0.0f, -1.0f};
    _mainCamera->SetCameraUpVec(cameraUpVec);

    // カーソル非表示
    auto gameWindow = Application::GetInstance().GetGameWindow();
    gameWindow->HideCursor();


    _isMoved = false;

    // マップ描画フラグをセット
    Application::GetInstance().SetIsDrawMap(true);
}

MovingPiece::~MovingPiece(){}