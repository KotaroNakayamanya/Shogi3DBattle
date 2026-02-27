#pragma once

#include<Windows.h>
#include<memory>

// ウィンドウプロシージャ宣言
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

class DX12;

class Application
{
private:
    // シングルトンパターン
    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;


    // ウインドウ用変数
    WNDCLASSEX _windowClass;
    HWND       _hwnd;

    const wchar_t* _WINDOW_CLASS_NAME = L"window";
    const wchar_t* _WINDOW_TITLE      = L"将棋大戦3D";

    const LONG _WINDOW_WIDTH = 1280;
    const LONG _WINDOW_HIGHT = 720;
    RECT       _WINDOW_RECT  = {0, 0, _WINDOW_WIDTH, _WINDOW_HIGHT};


    // ウインドウ用関数
    bool CreateGameWindow();
    void CreateWindowClass();
    void CreateWindowObject();
    void ExitGameWindow();

    // DX12オブジェクト
    std::shared_ptr<DX12> _dx12;


public:
    static Application& GetInstance();
    bool Init();
    void Run();
    void Exit(); 
};