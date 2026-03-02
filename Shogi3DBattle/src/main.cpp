#include"Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application& app = Application::GetInstance();

    if(app.Init() == false) return -1;

    app.Run();

    app.Exit();

    return 0;
}