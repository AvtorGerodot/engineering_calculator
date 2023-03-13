#pragma once

#include "stack.h"

//D:\Данил\прогание\C++\ingeneering calc

namespace ingeneeringcalc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		
		char* ConvertToCString(String^ str) {
			IntPtr^ ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
			return (char*)ptr->ToPointer();
		}
		
		myStack<char>* math_string_parse(String^ str) {
			//str->Replace(" ", "");
			printf("%s\n\n", ConvertToCString(str));
			
			int brackets_count = 0;
			myStack<char>* elements = new myStack<char>();
			//elements->isEmpty();

			String^ temp = L"";
			bool all_right = 1;
			for (int i = 0, comma = 0; i < str->Length && brackets_count >= 0 && all_right; i++) {
				if ((str[i] - '0' >= 0 && str[i] - '0' < 10) || str[i] == ',') { 
					temp += str[i]; 
					if (str[i] == ',') comma++; 
					if (comma > 1) all_right = 0;
				}
				else {
					if (temp->Length > 0) {
						elements->push(ConvertToCString(temp));
						temp = L"";
					}
					
				}
			}
			if (!all_right) {
				tb1->Text = L"ERROR";
				delete elements;
				elements = 0;
			}
			return elements;
		}
		
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ equals;
	private: System::Windows::Forms::TextBox^ tb1;
	protected:

	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->equals = (gcnew System::Windows::Forms::Button());
			this->tb1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// equals
			// 
			this->equals->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 28));
			this->equals->Location = System::Drawing::Point(490, 160);
			this->equals->Name = L"equals";
			this->equals->Size = System::Drawing::Size(80, 80);
			this->equals->TabIndex = 0;
			this->equals->Text = L"=";
			this->equals->UseVisualStyleBackColor = true;
			this->equals->Click += gcnew System::EventHandler(this, &MyForm::equals_Click);
			// 
			// tb1
			// 
			this->tb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->tb1->Location = System::Drawing::Point(12, 12);
			this->tb1->Multiline = true;
			this->tb1->Name = L"tb1";
			this->tb1->Size = System::Drawing::Size(558, 142);
			this->tb1->TabIndex = 1;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 253);
			this->Controls->Add(this->tb1);
			this->Controls->Add(this->equals);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void equals_Click(System::Object^ sender, System::EventArgs^ e) {
		if (tb1->Text->Length > 0) {
			String^ math_str = tb1->Text + '\n';
			tb1->Text = L"";
			myStack<char>* math_stack = math_string_parse(math_str);
			if(math_stack) math_stack->print();
		}
		else tb1->Text = L"0";
	}
	};
}