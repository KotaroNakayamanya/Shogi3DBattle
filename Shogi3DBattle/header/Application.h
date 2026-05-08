#pragma once

#include"GameWindow.h"
#include"DX12.h"
#include"InputHandler.h"
#include"I_SceneState.h"
#include"PiecePosManager.h"

#include"Camera.h"
#include"TextUI.h"
#include"I_Button.h"
#include"ButtonType.h"

#include"I_BufferedData.h"

#include"KeyMap.h"

#include"I_Texture.h"
#include"I_Piece.h"
#include"I_Board.h"

#include"BoardVertIndices.h"
#include"PieceVertIndices.h"

class Application
{
private:
    bool _isDrawMap = false;

    std::unique_ptr<GameWindow> _gameWindow; // ゲームウインドウ
    std::unique_ptr<DX12>       _dx12;       // DirectX


    // 将棋オブジェクト
    std::unique_ptr<I_Board>          _board;        // 将棋盤
    std::unique_ptr<BoardVertIndices> _boardIndices; // 将棋盤の頂点インデックス
    std::vector<std::unique_ptr<I_Piece>> _pieces;       // 駒
    std::unique_ptr<PieceVertIndices>     _pieceIndices; // 駒の頂点インデックス
    std::unique_ptr<PiecePosManager> _piecePosManager; // 駒の位置マネージャ
    void CreateGameObj(); // 将棋オブジェクト作成
    void CreatePlayerPieces(PlayerSide playerSide); // プレイヤーごとの駒作成

    // テクスチャ
    std::vector<std::unique_ptr<I_Texture>> _woodTexs; // 木材テクスチャ
    std::vector<std::unique_ptr<I_Texture>> _boardLineTexs; // 将棋盤黒線テクスチャ
    void CreateTex(); // テクスチャ作成

    // UI 
    std::vector<std::unique_ptr<UI>>     _frameUIs; // テキスト枠UI
    std::vector<std::unique_ptr<TextUI>> _textUIs;  // テキストUI
    std::vector<std::unique_ptr<I_Button>> _buttonUIs; // ボタンUI
    

    std::unique_ptr<I_SceneState>  _sceneState;   // シーンステート
    std::unique_ptr<InputHandler> _inputHandler; // インプットハンドラ
    std::unique_ptr<KeyMap>       _keyMap;       // キーマップ
    void InitKeyMap(); // 操作ボタン初期処理
    void InitSceneState(); // シーンステート初期処理

    // カメラ
    std::unique_ptr<Camera> _mainCamera; // メインカメラ
    std::unique_ptr<Camera> _mapCamera;  // マップカメラ
    void CreateCamera(); // カメラ作成


    Application(); // デフォルトコンストラクタ禁止
    Application(const Application&) = delete; // コピー禁止
    Application& operator=(const Application&) = delete; // 代入禁止

public:
    static Application& GetInstance(); // シングルトンインスタンスを返す

    void Init(); // 初期処理
    void Run();  // ゲーム実行処理
    void Exit(); // 終了処理

    DX12* GetDX12(); // DirectX12を返す
    GameWindow* GetGameWindow(); // ゲームウインドウオブジェクトを返す
    InputHandler* GetInputHandler(); // インプットハンドラを返す
    PiecePosManager* GetPiecePosManager(); // 駒の位置マネージャを返す

    I_Board* GetBoard(); // 将棋盤を返す
    std::vector<I_Piece*> GetPieces(); // 駒を返す
    std::vector<I_Texture*> GetWoodTexs(); // 木材テクスチャを返す
    std::vector<I_Texture*> GetBoardLineTexs(); // 将棋盤黒線テクスチャを返す
    NaturalBufferedData<unsigned short>* GetBoardVertIndices(); // 将棋盤頂点インデックスを返す
    NaturalBufferedData<unsigned short>* GetPieceVertIndices(); // 駒の頂点インデックスを返す
    KeyMap* GetKeyMap(); // 将棋盤頂点インデックスを返す

    std::vector<I_GameObj*> GetGameObjects(); // すべての将棋オブジェクトを返す
    std::vector<NaturalBufferedData<unsigned short>*> GetAllVertIndices(); // すべての頂点インデックスを返す

    
    Camera* GetMainCamera(); // メインカメラを返す
    Camera* GetMapCamera();  // マップカメラを返す

    void SetIsDrawMap(bool flag); // マップ描画フラグをセット
    bool IsDrawMap();             // マップ描画フラグを返す


    // テキストUIをプッシュ
    void PushTextUI(Text2D text2D);

    // ボタンUI作成
    void PushButton(
        ButtonType        buttonUIType,
        D2D1_RECT_F         rect);

    std::vector<UI*>     GetFrameUIs(); // テキスト枠UIを返す
    std::vector<TextUI*>     GetTextUIs(); // テキストUIを返す
    std::vector<I_Button*> GetButtons(); // ボタンUIを返す

    bool IsDrawUINotEmpty(); // UIの空状況を返す

    void RemoveAllUI();      // UIを全て削除する

    void ProcessChangeWindowSize(); // 画面サイズ変更処理

    ~Application() = default;
};