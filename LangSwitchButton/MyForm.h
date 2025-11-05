#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <tlhelp32.h>

#pragma comment(lib, "user32.lib")


static bool IsProcessRunningInMySession(const std::wstring& name) {
	DWORD mySessionId = 0;
	ProcessIdToSessionId(GetCurrentProcessId(), &mySessionId); // моя сессия

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32W pe{ sizeof(pe) };
	bool running = false;

	if (Process32FirstW(snap, &pe)) {
		do {
			if (_wcsicmp(pe.szExeFile, name.c_str()) == 0) {
				DWORD pidSession = 0;
				if (ProcessIdToSessionId(pe.th32ProcessID, &pidSession) && pidSession == mySessionId) {
					running = true;
					break;
				}
			}
		} while (Process32NextW(snap, &pe));
	}
	CloseHandle(snap);
	return running;
}


static void MonitorAndLogoffOnAbsence(const std::wstring& targetName,
	std::chrono::seconds timeout,
	std::chrono::seconds pollInterval)
{
	std::chrono::steady_clock::time_point missingSince{};
	bool wasMissing = false;

	for (;;) {
		//const bool running = IsProcessRunningByName(targetName);
		const bool running = IsProcessRunningInMySession(targetName);

		if (running) {
			wasMissing = false;
			missingSince = {};
		}
		else {
			if (!wasMissing) {
				wasMissing = true;
				missingSince = std::chrono::steady_clock::now();
			}
			else {
				const auto absentFor = std::chrono::steady_clock::now() - missingSince;
				if (absentFor >= timeout) {
					//ExitWindowsEx(EWX_LOGOFF, 0); // если нужно разлогиниться
					LockWorkStation();               // блокировка ПК
					break;                           
				}
			}
		}
		std::this_thread::sleep_for(pollInterval);
	}
}

namespace LangSwitchButton {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			UpdateLanguageButton();
			SetWindowPositionBottomRight();

			this->languageTimer = gcnew System::Windows::Forms::Timer();
			this->languageTimer->Interval = 100; 
			this->languageTimer->Tick += gcnew System::EventHandler(this, &MyForm::OnLanguageTimerTick);
			this->languageTimer->Start();
		}
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::Button^ LangButton;
		System::Windows::Forms::Timer^ languageTimer; 

	private: System::Windows::Forms::ToolStripMenuItem^ завершитьСеансToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ endSessionToolStripMenuItem;
	private: System::ComponentModel::IContainer^ components;
	


#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->LangButton = (gcnew System::Windows::Forms::Button());
			this->завершитьСеансToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->endSessionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// LangButton
			// 
			this->LangButton->AutoSize = true;
			this->LangButton->BackColor = System::Drawing::Color::SkyBlue;
			this->LangButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->LangButton->ForeColor = System::Drawing::Color::Blue;
			this->LangButton->Location = System::Drawing::Point(-2, -2);
			this->LangButton->Margin = System::Windows::Forms::Padding(0);
			this->LangButton->MaximumSize = System::Drawing::Size(40, 40);
			this->LangButton->MinimumSize = System::Drawing::Size(40, 40);
			this->LangButton->Name = L"LangButton";
			this->LangButton->Size = System::Drawing::Size(40, 40);
			this->LangButton->TabIndex = 0;
			this->LangButton->Text = L"EN";
			this->LangButton->UseVisualStyleBackColor = false;
			this->LangButton->Click += gcnew System::EventHandler(this, &MyForm::LangButton_Click);
			this->LangButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::LangButton_MouseDown);
			// 
			// завершитьСеансToolStripMenuItem
			// 
			this->завершитьСеансToolStripMenuItem->Name = L"завершитьСеансToolStripMenuItem";
			this->завершитьСеансToolStripMenuItem->Size = System::Drawing::Size(32, 19);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->endSessionToolStripMenuItem });
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(181, 48);
			// 
			// endSessionToolStripMenuItem
			// 
			this->endSessionToolStripMenuItem->Name = L"endSessionToolStripMenuItem";
			this->endSessionToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->endSessionToolStripMenuItem->Text = L"End Session";
			this->endSessionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::endSessionToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(36, 36);
			this->ControlBox = false;
			this->Controls->Add(this->LangButton);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximumSize = System::Drawing::Size(36, 36);
			this->MinimumSize = System::Drawing::Size(36, 36);
			this->Name = L"MyForm";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->TopMost = true;
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
		void SetWindowPositionBottomRight()
		{
			int screenWidth = Screen::PrimaryScreen->WorkingArea.Width;
			int screenHeight = Screen::PrimaryScreen->WorkingArea.Height;

			int windowWidth = this->Width;
			int windowHeight = this->Height;

			this->Left = screenWidth - windowWidth;
			this->Top = screenHeight - windowHeight;
		}
#pragma endregion
	
	
	System::Void LangButton_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		System::Drawing::Point pos = this->LangButton->PointToScreen(System::Drawing::Point(0, 0));
		this->contextMenuStrip1->Show(pos);

		return;
	}
}
	
	

	private:
		void UpdateLanguageButton()
		{

			HWND hwnd = GetForegroundWindow();
			if (hwnd == NULL)
			{
				this->LangButton->Text = L"??";
				this->LangButton->ForeColor = Color::Gray;
				return;
			}

			DWORD threadId = GetWindowThreadProcessId(hwnd, NULL);

			HKL hkl = GetKeyboardLayout(threadId);
			unsigned short lang = static_cast<unsigned short>(reinterpret_cast<UINT_PTR>(hkl) & 0xFFFF);

			String^ text;
			Color textColor;

			switch (lang)
			{
			case 0x0409: // English (US)
				text = L"EN";
				textColor = Color::Blue;
				break;
			case 0x0419: // Russian
				text = L"RU";
				textColor = Color::Blue;
				break;
			case 0x0422: // Ukrainian
				text = L"UK";
				textColor = Color::Blue;
				break;
			default:
				text = L"??";
				textColor = Color::Gray;
				break;
			}

			this->LangButton->Text = text;
			this->LangButton->ForeColor = textColor;
		}

	private: System::Void OnLanguageTimerTick(System::Object^ sender, System::EventArgs^ e) {
		UpdateLanguageButton();
	}
	
	private: System::Void LangButton_Click(System::Object^ sender, System::EventArgs^ e) {

		HWND previousWindow = GetForegroundWindow();
		if (previousWindow == NULL) return;

		DWORD previousThreadId = GetWindowThreadProcessId(previousWindow, NULL);
		DWORD currentThreadId = GetCurrentThreadId(); 

		if (currentThreadId != previousThreadId)
			AttachThreadInput(currentThreadId, previousThreadId, TRUE);

		HWND hwnd = GetForegroundWindow();
		if (hwnd == NULL) return;
		DWORD threadId = GetWindowThreadProcessId(hwnd, NULL);
		HKL hkl = GetKeyboardLayout(threadId);
		unsigned short lang = static_cast<unsigned short>(reinterpret_cast<UINT_PTR>(hkl) & 0xFFFF);

		HKL newLayout = NULL;
		switch (lang)
		{
		case 0x0409: newLayout = LoadKeyboardLayout(L"00000419", KLF_ACTIVATE); break;
		case 0x0419: newLayout = LoadKeyboardLayout(L"00000422", KLF_ACTIVATE); break;
		case 0x0422: newLayout = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); break;
		default: newLayout = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); break;
		}

		if (newLayout != NULL)
			PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, reinterpret_cast<LPARAM>(newLayout));

		if (currentThreadId != previousThreadId)
			AttachThreadInput(currentThreadId, previousThreadId, FALSE);

		SetForegroundWindow(previousWindow);
	}
	

	//DLL Library

		   [DllImport("user32.dll")]
			   static HWND GetForegroundWindow();

		   [DllImport("user32.dll")]
			   static DWORD GetWindowThreadProcessId(HWND hWnd, LPVOID lpdwProcessId);

		   [DllImport("user32.dll")]
			   static HKL GetKeyboardLayout(DWORD threadId);

		   [DllImport("user32.dll", CharSet = CharSet::Auto)]
			   static HKL LoadKeyboardLayout(String^ pwszKLID, UINT Flags);

		   [DllImport("user32.dll")]
			   static BOOL PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		   [DllImport("user32.dll")]
			   static BOOL AttachThreadInput(DWORD idAttach, DWORD idAttachTo, BOOL fAttach);

		   [DllImport("user32.dll")]
			   static BOOL SetForegroundWindow(HWND hWnd);
	
private: System::Void endSessionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	LockWorkStation();
}
};
}
