#pragma once

#include<memory>

class GameWindow;
class DX12;
class KeyMap;

class Application
{
private:
    std::unique_ptr<GameWindow> _gameWindow; // ゲームウインドウオブジェクト
    std::unique_ptr<DX12> _dx12; // DX12オブジェクト
    std::unique_ptr<KeyMap> _keyMap; // キーマップオブジェクト

    Application(); // デフォルトコンストラクタ禁止
    Application(const Application&) = delete; // コピー禁止
    Application& operator=(const Application&) = delete; // 代入禁止

public:
    static Application& GetInstance(); // シングルトンインスタンスを返す

    bool Init(); // 初期処理
    void Run();  // ゲーム実行処理
    void Exit(); // 終了処理

    KeyMap* GetKeyMapObj(); // キーマップオブジェクトを返す

    ~Application();
};