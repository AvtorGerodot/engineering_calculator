#pragma once

#include "stack.h"
#include <string.h>

//D:\ƒанил\прогание\C++\ingeneering calc

namespace ingeneeringcalc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
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
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		
		char* ConvertToCString(String^ str) {
			IntPtr^ ptr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
			/*const char* const_ptr = (char*)ptr->ToPointer();
			char* dynamic_ptr = new char[strlen(const_ptr)];*/
			return (char*)ptr->ToPointer();
		}
		
		myStack<char>* math_string_parse(String^ str) {
			str = str->Replace(" ", "");
			printf("%s\n\n", ConvertToCString(str));
			
			int brackets_count = 0;
			myStack<char>* elements = new myStack<char>();
			//elements->isEmpty();

			String^ temp = L"";
			bool all_right = 1, dual_operator = 0;
			for (int i = 0, comma = 0; i < str->Length && all_right; i++) {
				if ((str[i] - '0' >= 0 && str[i] - '0' < 10) || str[i] == ',') { 
					//переписать логику
					temp += str[i];
					dual_operator = 0;
					if (str[i] == ',') comma++; 
				}
				else {
					if (temp->Length > 0) {
						elements->push(ConvertToCString(temp));
						temp = L"";
						comma = 0;
					}

					String^ operators = L"+-*/()";
					String^ trigonom_func = L"sin cos tan ctg";
					temp = str[i].ToString();
					if (operators->Contains(temp)) {
						elements->push(ConvertToCString(temp));
						temp = L"";
						if (str[i] == '(') { brackets_count++; dual_operator = 0; }
						else if (str[i] == ')') { brackets_count--; dual_operator = 0; }
						else dual_operator++;
					}
					else if (str[i] == 's' || str[i] == 'c' || str[i] == 't') {
						for (int tick = 1; i + tick < str->Length && tick < 3; tick++)
							temp += str[i + tick].ToString();
						i += 2;
						printf("%s|%c\n", ConvertToCString(temp), str[i]);
						if (trigonom_func->Contains(temp)) elements->push(ConvertToCString(temp));
						else all_right = 0;
						temp = L"";
					}
					else all_right = 0;
				}
				//всевозможные проверки
				if (dual_operator > 1 || brackets_count < 0 || comma > 1) all_right = 0;
			}
			if (temp->Length > 0) {
				elements->push(ConvertToCString(temp));
				temp = L"";
				//dual_operator = 0;
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
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
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
			this->tb1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::tb1_Click);
			this->tb1->TextChanged += gcnew System::EventHandler(this, &MyForm::tb1_TextChanged);
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
			String^ math_str = tb1->Text;
			tb1->Text = L"";
			myStack<char>* math_stack = math_string_parse(math_str);
			if (math_stack) {
				math_stack->print();
				delete math_stack;
			}
		}
		else tb1->Text = L"0";
	}
	private: System::Void tb1_Click(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (tb1->Text == L"0" || tb1->Text == L"ERROR") tb1->Text = L"";
	}

	private: System::Void tb1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}