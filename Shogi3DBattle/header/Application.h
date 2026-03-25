#pragma once

#include"GameWindow.h"
#include"DX12.h"
#include"InputHandler.h"
#include"IShogiObjFactory.h"


class Application
{
private:
    std::unique_ptr<GameWindow>            _gameWindow; // ゲームウインドウ
    std::unique_ptr<Board>                 _board;      // 将棋盤
    std::vector<std::unique_ptr<Piece>>    _pieces;     // 駒
    std::unique_ptr<DX12>                  _dx12;       // DirectX

    std::unique_ptr<IShogiObjFactory> _shogiObjFactory; // 将棋オブジェクトファクトリー

    void CreateShogiObj(); // 将棋オブジェクト作成

    // テクスチャ
    std::unique_ptr<Tex> _woodTex; // 木材テクスチャ
    std::unique_ptr<Tex> _boardLineTex; // 将棋盤黒線テクスチャ
    

    void CreateTex(); // テクスチャ作成


    std::unique_ptr<InputHandler> _inputHandler; // インプットハンドラ

    Application(); // デフォルトコンストラクタ禁止
    Application(const Application&) = delete; // コピー禁止
    Application& operator=(const Application&) = delete; // 代入禁止

public:
    static Application& GetInstance(); // シングルトンインスタンスを返す

    bool Init(); // 初期処理
    void Run();  // ゲーム実行処理
    void Exit(); // 終了処理

    GameWindow* GetGameWindow(); // ゲームウインドウオブジェクトを返す
    DX12* GetDX12(); // DX12オブジェクトを返す
    HWND GetHWND(); // ウインドウハンドルを返す

    Board* GetBoard(); // 将棋盤を返す
    std::vector<std::unique_ptr<Piece>>& GetPieces(); // 駒を返す
    Tex* GetWoodTex(); // 木材テクスチャを返す
    Tex* GetBoardLineTex(); // 将棋盤黒線テクスチャを返す

    InputHandler* GetInputHandler(); // インプットハンドラを返す

    UINT GetWindowWidth();  // ウインドウ横サイズを返す
    UINT GetWindowHeight(); // ウインドウ縦サイズを返す
    
    ViewMat* GetViewMat();

    void ProcessChangeWindowSize(); // 画面サイズ変更処理

    ~Application();
};