#include"Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Application& app = Application::GetInstance();

    if(app.Init() == false) return -1;

    app.Run();

    app.Exit();

    return 0;
}