
#include "MyForm1.h"
#include "myclass.h"
#pragma once

namespace course {

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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ exit;

	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::Button^ successfull;



	private: System::Windows::Forms::Label^ label3;
	protected:

	protected:




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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->exit = (gcnew System::Windows::Forms::Button());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->successfull = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// exit
			// 
			this->exit->BackColor = System::Drawing::Color::Gray;
			this->exit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit->ForeColor = System::Drawing::Color::White;
			this->exit->Location = System::Drawing::Point(216, 130);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(72, 26);
			this->exit->TabIndex = 0;
			this->exit->Text = L"Выход";
			this->exit->UseVisualStyleBackColor = false;
			this->exit->Click += gcnew System::EventHandler(this, &MyForm::exit_Click);
			// 
			// password
			// 
			this->password->BackColor = System::Drawing::Color::Gray;
			this->password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->password->ForeColor = System::Drawing::Color::White;
			this->password->Location = System::Drawing::Point(115, 104);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(173, 20);
			this->password->TabIndex = 3;
			// 
			// successfull
			// 
			this->successfull->BackColor = System::Drawing::Color::Gray;
			this->successfull->Cursor = System::Windows::Forms::Cursors::Hand;
			this->successfull->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->successfull->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->successfull->ForeColor = System::Drawing::Color::White;
			this->successfull->Location = System::Drawing::Point(115, 130);
			this->successfull->Name = L"successfull";
			this->successfull->Size = System::Drawing::Size(72, 26);
			this->successfull->TabIndex = 4;
			this->successfull->Text = L"Готово";
			this->successfull->UseVisualStyleBackColor = false;
			this->successfull->Click += gcnew System::EventHandler(this, &MyForm::successfull_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(111, 77);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(177, 24);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Введите пароль:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->successfull);
			this->Controls->Add(this->password);
			this->Controls->Add(this->exit);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"House Agency";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void successfull_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ pass = this->password->Text;
		Password^ myPassword = gcnew Password();
		if (myPassword->check(pass)) {
			MyForm1^ form2 = gcnew MyForm1();
			form2->Show();
			MyForm::Hide();
		}
		else
			MessageBox::Show(this, "Вы ввели неверный пароль!", "Сообщение",MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
};
}
