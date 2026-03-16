#pragma once

#include"GameWindow.h"
//#include"GameObj.h"
#include"DX12.h"
#include"InputHandler.h"


class Application
{
private:
    std::unique_ptr<GameWindow> _gameWindow; // ゲームウインドウ
    //std::unique_ptr<GameObj> _gameObj; // ゲームオブジェクト
    std::unique_ptr<DX12> _dx12; // DirectX
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
    InputHandler* GetInputHandler(); // インプットハンドラを返す
    UINT GetWindowWidth();  // ウインドウ横サイズを返す
    UINT GetWindowHeight(); // ウインドウ縦サイズを返す
    
    ViewMat* GetViewMat();

    void ProcessChangeWindowSize(); // 画面サイズ変更処理

    ~Application();
};