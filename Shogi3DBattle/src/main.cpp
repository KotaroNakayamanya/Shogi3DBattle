#include<Windows.h>
#include"Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application& app = Application::GetInstance();

    if(app.Init() == false) return -1; // 初期化処理

    app.Run(); // ゲーム実行

    app.Exit(); // 終了処理

    return 0;
}