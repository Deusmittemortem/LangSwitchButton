#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>

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

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->LangButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// LangButton
			// 
			this->LangButton->AutoSize = true;
			this->LangButton->Location = System::Drawing::Point(3, 2);
			this->LangButton->Name = L"LangButton";
			this->LangButton->Size = System::Drawing::Size(41, 32);
			this->LangButton->TabIndex = 0;
			this->LangButton->Text = L"Lang";
			this->LangButton->UseVisualStyleBackColor = true;
			this->LangButton->Click += gcnew System::EventHandler(this, &MyForm::LangButton_Click);
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(30, 30);
			this->ControlBox = false;
			this->Controls->Add(this->LangButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximumSize = System::Drawing::Size(46, 36);
			this->MinimumSize = System::Drawing::Size(46, 36);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->TopMost = true;

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
				textColor = Color::Red;
				break;
			case 0x0419: // Russian
				text = L"RU";
				textColor = Color::Blue;
				break;
			case 0x0422: // Ukrainian
				text = L"UK";
				textColor = Color::Green;
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
	};
}
