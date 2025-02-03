#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    LangSwitchButton::MyForm form;
    Application::Run(% form);
}
