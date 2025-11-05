#include "MyForm.h"
#include <thread>
#include <chrono>

using namespace std::chrono;
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    std::thread procMon(
        MonitorAndLogoffOnAbsence,
        std::wstring(L"1cv8.exe"), 
        seconds(20),                  
        seconds(8)                    
    );
    procMon.detach();

    LangSwitchButton::MyForm form;
    Application::Run(% form);

    return 0;
}