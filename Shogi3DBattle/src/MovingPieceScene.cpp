#include"MovingPieceScene.h"
#include"Application.h"
#include"SelectingPieceScene.h"
#include"VecCalc.h"
#include<cmath>
#include"RuleManager.h"

// 駒操作シーン動作
std::unique_ptr<I_SceneState> MovingPieceScene::ExeSceneProcess(
    UCHAR inputMemory,
    int cursorX,
    int cursorY,
    int cursorXMove,
    int cursorYMove)
{
    std::unique_ptr<I_SceneState> newSceneState = nullptr;

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
        return ExeDecisionButtonProcess();
    if(inputMemory & InputHandler::CANCEL)    // キャンセルボタン処理
        return ExeCancelButton();


    

    return newSceneState;
}

// ワールド行列から行位置を返す
unsigned int MovingPieceScene::GetRowFromWorldMat(WorldMat worldMat)
{
    auto float4x4 = VecCalc::GetFoloat4x4FromMat(worldMat.GetMat());
    auto y        = float4x4._42;
    auto row      = static_cast<unsigned int>(std::round(y/10.0f));

    return row;
}

// ワールド行列から列位置を返す
unsigned int MovingPieceScene::GetColumnFromWorldMat(WorldMat worldMat)
{
    auto float4x4 = VecCalc::GetFoloat4x4FromMat(worldMat.GetMat());
    auto x        = float4x4._41;
    auto column   = static_cast<unsigned int>(std::round(x/10.0f));

    return column;
}


// 決定ボタン
std::unique_ptr<I_SceneState> MovingPieceScene::ExeDecisionButtonProcess()
{
    //// 動かし始めの位置から移動しているか確認する
    //auto oldRow      = GetRowFromWorldMat   (_startWorldMat);
    //auto oldColumn   = GetColumnFromWorldMat(_startWorldMat);

    //auto newWorldMat = _piece->GetWorldMat();
    //auto newRow      = GetRowFromWorldMat   (*newWorldMat);
    //auto newColumn   = GetColumnFromWorldMat(*newWorldMat);

    //auto isChangedRow    = oldRow    != newRow;
    //auto isChangedColumn = oldColumn != newColumn;

    //if(!isChangedRow && !isChangedColumn) return nullptr; // 移動がなければ何もしない

    // その位置に駒が移動可能かどうか確認し、可能でなければ何もしない
    auto worldMat = _piece->GetWorldMat();
    auto row      = GetRowFromWorldMat   (*worldMat);
    auto column   = GetColumnFromWorldMat(*worldMat);
    if (!RuleManager::GetCanThisPlacedPiece(_piece, row, column)) return nullptr;

    // 新しい位置に記録する
    auto piecePosManager = Application::GetInstance().GetPiecePosManager();
    piecePosManager->PlacePieceOnBoard(_piece, row, column);

    //// 可能であれば、駒を移動後の位置に記録する
    //if (isThisPosOK)
    //{
    //    auto piecePosManager = Application::GetInstance().GetPiecePosManager();
    //    piecePosManager->PlacePieceOnBoard(_piece, newRow, newColumn);
    //}

    // 勝利条件を満たしているかどうか確認する
    auto isWinning = RuleManager::IsWinning(PlayerSide::PLAYER_1);

    // 勝利していなければ相手にターンを渡してゲーム続行
    auto opponentPlayer = _piece->GetPlayerSide() == PlayerSide::PLAYER_1 ?
        PlayerSide::PLAYER_2 : PlayerSide::PLAYER_1;
    auto& app = Application::GetInstance();
    app.SetCurrentPlayerTurn(opponentPlayer);
    
    return std::make_unique<SelectingPieceScene>();
}

// キャンセルボタン処理
std::unique_ptr<I_SceneState> MovingPieceScene::ExeCancelButton()
{
    std::unique_ptr<I_SceneState> newSceneState;
    if (_isMoved) // 駒を動かしていたら駒を初期位置に戻し、カメラとフォーカスを平行移動する
    {
        // 元の位置に動かすまでのベクトルを取得
        auto worldMat = _piece->GetWorldMat();
        auto subtMat = _startWorldMat.GetMat() - worldMat->GetMat();
        auto subtFloat4x4 = VecCalc::GetFoloat4x4FromMat(subtMat);
        auto vecX = subtFloat4x4._41;
        auto vecY = subtFloat4x4._42;
        auto vecZ = 0.0f;
        DirectX::XMFLOAT3 moveVec = {vecX, vecY, vecZ};

        // 駒のワールド行列を初期化、カメラを平行移動
        _piece->GetWorldMat()->SetMat(_startWorldMat.GetMat());
        _mainCamera->MoveCameraPos(moveVec);
        _mainCamera->MoveFocusPos (moveVec);

        // 駒は動いてない状態に
        _isMoved = false;
        newSceneState = nullptr;
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
        newSceneState = std::make_unique<SelectingPieceScene>();
    }

    return newSceneState;
}

// 駒とカメラを動かす
void MovingPieceScene::MovePieceAndCamera(DirectX::XMFLOAT3 vec)
{
    _piece->Move(vec);
    _mainCamera->MoveCameraPos(vec);
    _mainCamera->MoveFocusPos (vec);
    _isMoved = true;
}

// マウス移動処理
void MovingPieceScene::ExeMouseMove(int xMove, int yMove)
{
    float fx = xMove / 1000.0f;
    float fy = yMove / 1000.0f;

    _mainCamera->RotationH(fx); // 水平方向にカメラ回転
    _mainCamera->RotationV(fy); // 垂直方向にカメラ回転
}





MovingPieceScene::MovingPieceScene(I_Piece* piece)
{
    auto& app = Application::GetInstance();

    _piece = piece; // 操作対象の駒を取得
    _mainCamera = app.GetMainCamera(); // メインカメラ取得
    
    auto worldMat = piece->GetWorldMat()->GetMat(); // 駒のワールド行列取得
    _startWorldMat = *piece->GetWorldMat(); // ワールド行列初期値として取得しておく

    // 駒が移動可能な位置を取得する
    _canPlaced = RuleManager::GetCanPlaced(piece);
    
    // カメラのフォーカス位置を駒の位置を基準にセット
    auto worldFloat4x4 = VecCalc::GetFoloat4x4FromMat(worldMat);
    auto focusX = worldFloat4x4._41;
    auto focusY = worldFloat4x4._42;
    auto focusZ = worldFloat4x4._43 - 8.0f;
    DirectX::XMFLOAT3 focusPos = {focusX, focusY, focusZ};
    _mainCamera->SetFocusPos(focusPos);

    // カメラの位置をフォーカス位置に合わせてセット
    float offsetY = -10.0f;
    float offsetZ = -10.0f;
    if(piece->GetPlayerSide() == PlayerSide::PLAYER_1) offsetY = -offsetY;
    DirectX::XMFLOAT3 cameraPos = {focusX, focusY+offsetY, focusZ+offsetZ};
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

MovingPieceScene::~MovingPieceScene()
{
    // カーソル表示
    auto gameWindow = Application::GetInstance().GetGameWindow();
    gameWindow->ShowCursor();

    // マップ描画フラグ解除
    Application::GetInstance().SetIsDrawMap(false);
}