#pragma once

#include"GameWindow.h"
#include"DX12.h"
#include"InputHandler.h"
#include"I_GameObjFactory.h"
#include"I_SceneState.h"
#include"IBufferedDataFactory.h"

#include"Camera.h"
#include"I_ButtonUI.h"
#include"ButtonUIType.h"

#include"BufferedData.h"
#include"VertStruct.h"

#include"I_ButtonUIFactory.h"
#include"KeyMap.h"

#include"Texture.h"

class Application
{
private:
    std::unique_ptr<GameWindow> _gameWindow; // ゲームウインドウ
    std::unique_ptr<DX12>       _dx12;       // DirectX


    // 将棋オブジェクト
    std::unique_ptr<Board>                        _board;        // 将棋盤
    std::unique_ptr<NaturalBufferedData<unsigned short>> _boardIndices; // 将棋盤の頂点インデックス

    std::vector<std::unique_ptr<I_Piece>>           _pieces;       // 駒
    std::unique_ptr<NaturalBufferedData<unsigned short>> _pieceIndices; // 駒の頂点インデックス

    void CreateGameObj(); // 将棋オブジェクト作成

    // ファクトリー
    std::unique_ptr<I_GameObjFactory>    _gameObjFactory;    // ゲームオブジェクトファクトリー
    std::unique_ptr<IBufferedDataFactory>  _verticesFactory;    // 頂点集合ファクトリー
    std::unique_ptr<IBufferedDataFactory> _vertIndicesFactory; // インデックス集合ファクトリー
    std::unique_ptr<IBufferedDataFactory> _texFactory;    // テクスチャファクトリー


    // テクスチャ
    std::unique_ptr<Texture> _woodTex; // 木材テクスチャ
    std::vector<std::unique_ptr<Texture>> _boardLineTexs; // 将棋盤黒線テクスチャ
    void CreateTex(); // テクスチャ作成


    // UI 
    std::vector<std::unique_ptr<I_ButtonUI>> _buttonUIs; // ボタンUI
    std::unique_ptr<I_ButtonUIFactory> _buttonUIFactory; // ボタンUIファクトリー


    

    std::unique_ptr<I_SceneState>  _sceneState;   // シーンステート
    std::unique_ptr<InputHandler> _inputHandler; // インプットハンドラ
    std::unique_ptr<KeyMap>       _keyMap;       // キーマップ
    void InitKeyMap(); // 操作ボタン初期処理
    void InitSceneState(); // シーンステート初期処理

    

    


    // カメラ
    std::unique_ptr<Camera> _mainCamera; // メインカメラ
    std::unique_ptr<Camera> _mapCamera;  // マップカメラ
    void CreateCamera(); // カメラ作成

    // シーン更新チェック
    bool IsUpdatedScene(I_SceneState* sceneState);

    bool _isDrawMap = false;


    

    Application(); // デフォルトコンストラクタ禁止
    Application(const Application&) = delete; // コピー禁止
    Application& operator=(const Application&) = delete; // 代入禁止

public:
    static Application& GetInstance(); // シングルトンインスタンスを返す

    bool Init(); // 初期処理
    void Run();  // ゲーム実行処理
    void Exit(); // 終了処理

    GameWindow* GetGameWindow(); // ゲームウインドウオブジェクトを返す

    Board* GetBoard(); // 将棋盤を返す
    std::vector<std::unique_ptr<I_Piece>>& GetPieces(); // 駒を返す
    Texture* GetWoodTex(); // 木材テクスチャを返す
    std::vector<std::unique_ptr<Texture>>& GetBoardLineTexs(); // 将棋盤黒線テクスチャを返す
    NaturalBufferedData<unsigned short>* GetBoardVertIndices(); // 将棋盤頂点インデックスを返す
    NaturalBufferedData<unsigned short>* GetPieceVertIndices(); // 駒の頂点インデックスを返す
    KeyMap* GetKeyMap(); // 将棋盤頂点インデックスを返す

    std::vector<I_GameObj*> GetGameObjects(); // すべての将棋オブジェクトを返す
    std::vector<BufferedData*> GetAllVertIndices(); // すべての頂点インデックスを返す

    InputHandler* GetInputHandler(); // インプットハンドラを返す
    
    Camera* GetMainCamera(); // メインカメラを返す
    Camera* GetMapCamera();  // マップカメラを返す

    void SetIsDrawMap(bool flag); // マップ描画フラグをセット
    bool IsDrawMap();             // マップ描画フラグを返す

    // ボタンUI
    template<typename T>
    void CreateButtonUI( // ボタンUIをプッシュする
        D2D1_RECT_F              rect,
        std::vector<TextAndRect> textAndRects);

    std::vector<std::unique_ptr<I_ButtonUI>>& GetButtonUIs(); // ボタンUIを返す

    bool IsDrawUINotEmpty(); // UIの空状況を返す

    void RemoveAllUI();      // UIを全て削除する

    void ProcessChangeWindowSize(); // 画面サイズ変更処理

    ~Application() = default;
};

// ボタンUIプッシュ
template<typename T>
void Application::CreateButtonUI(
    D2D1_RECT_F              rect,
    std::vector<TextAndRect> textAndRects)
{
    _buttonUIFactory.reset(new T());
    _buttonUIs.push_back(_buttonUIFactory->CreateButtonUI(rect, textAndRects));
}