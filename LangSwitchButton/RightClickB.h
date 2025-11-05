#pragma once

namespace LangSwitchButton {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для RightClickB
	/// </summary>
	public ref class RightClickB : public System::Windows::Forms::Form
	{
	public:
		RightClickB(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~RightClickB()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ завершитьСеансToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^ завершитьСеансToolStripMenuItem1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->завершитьСеансToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip2 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->завершитьСеансToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1->SuspendLayout();
			this->contextMenuStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->завершитьСеансToolStripMenuItem });
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(170, 26);
			// 
			// завершитьСеансToolStripMenuItem
			// 
			this->завершитьСеансToolStripMenuItem->Name = L"завершитьСеансToolStripMenuItem";
			this->завершитьСеансToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->завершитьСеансToolStripMenuItem->Text = L"Завершить сеанс";
			// 
			// contextMenuStrip2
			// 
			this->contextMenuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->завершитьСеансToolStripMenuItem1 });
			this->contextMenuStrip2->Name = L"contextMenuStrip2";
			this->contextMenuStrip2->Size = System::Drawing::Size(170, 26);
			// 
			// завершитьСеансToolStripMenuItem1
			// 
			this->завершитьСеансToolStripMenuItem1->Name = L"завершитьСеансToolStripMenuItem1";
			this->завершитьСеансToolStripMenuItem1->Size = System::Drawing::Size(169, 22);
			this->завершитьСеансToolStripMenuItem1->Text = L"Завершить сеанс";
			// 
			// RightClickB
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(325, 277);
			this->Name = L"RightClickB";
			this->Text = L"RightClickB";
			this->contextMenuStrip1->ResumeLayout(false);
			this->contextMenuStrip2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
