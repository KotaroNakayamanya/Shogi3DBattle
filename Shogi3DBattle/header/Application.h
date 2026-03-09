#pragma once

#include"GameWindow.h"
#include"DX12.h"
#include"InputHandler.h"

class Application
{
private:
    UINT _width  = 1280; // 画面横サイズ
    UINT _height =  720; // 画面縦サイズ

    std::unique_ptr<GameWindow> _gameWindow; // ゲームウインドウオブジェクト
    std::unique_ptr<DX12> _dx12; // DX12オブジェクト
    std::unique_ptr<InputHandler> _inputHandler; // インプットハンドラ

    Application(); // デフォルトコンストラクタ禁止
    Application(const Application&) = delete; // コピー禁止
    Application& operator=(const Application&) = delete; // 代入禁止

public:
    static Application& GetInstance(); // シングルトンインスタンスを返す

    UINT GetWindowWidth();  // ウインドウ横サイズを返す
    UINT GetWindowHeight(); // ウインドウ縦サイズを返す

    bool Init(); // 初期処理
    void Run();  // ゲーム実行処理
    void Exit(); // 終了処理

    InputHandler* GetInputHandler(); // インプットハンドラを返す

    void ProcessChangeWindowSize(); // 画面サイズ変更処理

    ~Application();
};