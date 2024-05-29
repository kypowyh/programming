#pragma once

#include "myclass.h"

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для EnterForm2
	/// </summary>
	public ref class EnterForm2 : public System::Windows::Forms::Form
	{
	public:
		EnterForm2(void)
		{
			InitializeComponent();
			ShowInTaskbar = false;
			//
			//TODO: добавьте код конструктора
			//

		}
		String^ GetName() {
			return name->Text;
		}

		int GetAge() {
			return Convert::ToInt32(age->Text);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~EnterForm2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Save;
	protected:
	private: System::Windows::Forms::TextBox^ name;
	private: System::Windows::Forms::TextBox^ age;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EnterForm2::typeid));
			this->Save = (gcnew System::Windows::Forms::Button());
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->age = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Save
			// 
			this->Save->BackColor = System::Drawing::Color::Gray;
			this->Save->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Save->ForeColor = System::Drawing::Color::White;
			this->Save->Location = System::Drawing::Point(79, 161);
			this->Save->Name = L"Save";
			this->Save->Size = System::Drawing::Size(213, 48);
			this->Save->TabIndex = 0;
			this->Save->Text = L"Сохранить";
			this->Save->UseVisualStyleBackColor = false;
			this->Save->Click += gcnew System::EventHandler(this, &EnterForm2::Save_Click);
			// 
			// name
			// 
			this->name->BackColor = System::Drawing::Color::Gray;
			this->name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name->ForeColor = System::Drawing::Color::White;
			this->name->Location = System::Drawing::Point(79, 50);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(213, 20);
			this->name->TabIndex = 1;
			// 
			// age
			// 
			this->age->BackColor = System::Drawing::Color::Gray;
			this->age->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->age->ForeColor = System::Drawing::Color::White;
			this->age->Location = System::Drawing::Point(79, 109);
			this->age->Name = L"age";
			this->age->Size = System::Drawing::Size(213, 20);
			this->age->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(76, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(135, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Введите имя жильца:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(76, 93);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(160, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Введите возраст жильца:";
			// 
			// EnterForm2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->age);
			this->Controls->Add(this->name);
			this->Controls->Add(this->Save);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"EnterForm2";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"EnterForm2";
			this->Load += gcnew System::EventHandler(this, &EnterForm2::EnterForm2_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
		int resage;
		if (!Int32::TryParse(age->Text, resage) || resage < 0) {
			MessageBox::Show("Пожалуйста, введите корректный положительный возраст.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return; 
		}
		this->Close();
	}
	private: System::Void EnterForm2_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
