#pragma once

#include "stack.h"

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
		
		myStack<String^> ^ math_string_parse(String^ str) {
			int brackets_count = 0;
			myStack<String^>^ elements = gcnew myStack<String^>();
			//elements->isEmpty();

			for (int i = 0, numflag = 0, start = 0; i < str->Length && brackets_count >= 0; i++) {
				if (str[i] - '0' < 10 || str[i] == ',') numflag = 1;
				else {
					if (numflag) {
						//можно ли написать нормально?
						//String^ systemstring = gcnew String(orig);
						array<wchar_t>^ temp;
						str->CopyTo(start, temp, 0, i-start);
						elements->push(gcnew String(temp));
						numflag = 0;
					}
					start = i;
				}
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
			myStack<String^>^ math_stack = math_string_parse(math_str);
			math_stack->print();
		}
		else tb1->Text = L"0";
		/*myStack<String^>^ st = gcnew myStack<String^>();
		st->push(L"123");
		st->push(L"456");
		st->print();
		String^ a;
		st->pop(a);
		st->print();*/
	}
	};
}
