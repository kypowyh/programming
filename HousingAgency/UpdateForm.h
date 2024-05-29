#pragma once

#include "myclass.h"
#include "RemForm.h"
#include "AddForm.h"

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для UpdateForm
	/// </summary>
	public ref class UpdateForm : public System::Windows::Forms::Form
	{
	public:
		UpdateForm(void)
		{
			InitializeComponent();
			ShowInTaskbar = false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~UpdateForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ number;
	private: System::Windows::Forms::Button^ cont;
	private: System::Windows::Forms::Button^ exit;
	private: System::Windows::Forms::TextBox^ num;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UpdateForm::typeid));
			this->number = (gcnew System::Windows::Forms::TextBox());
			this->cont = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->num = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// number
			// 
			this->number->BackColor = System::Drawing::Color::Gray;
			this->number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->number->ForeColor = System::Drawing::Color::White;
			this->number->Location = System::Drawing::Point(70, 57);
			this->number->Name = L"number";
			this->number->Size = System::Drawing::Size(244, 20);
			this->number->TabIndex = 0;
			// 
			// cont
			// 
			this->cont->BackColor = System::Drawing::Color::Gray;
			this->cont->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cont->ForeColor = System::Drawing::Color::White;
			this->cont->Location = System::Drawing::Point(70, 182);
			this->cont->Name = L"cont";
			this->cont->Size = System::Drawing::Size(96, 40);
			this->cont->TabIndex = 1;
			this->cont->Text = L"Продолжить";
			this->cont->UseVisualStyleBackColor = false;
			this->cont->Click += gcnew System::EventHandler(this, &UpdateForm::cont_Click);
			// 
			// exit
			// 
			this->exit->BackColor = System::Drawing::Color::Gray;
			this->exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit->ForeColor = System::Drawing::Color::White;
			this->exit->Location = System::Drawing::Point(218, 182);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(96, 40);
			this->exit->TabIndex = 2;
			this->exit->Text = L"Выход";
			this->exit->UseVisualStyleBackColor = false;
			this->exit->Click += gcnew System::EventHandler(this, &UpdateForm::exit_Click);
			// 
			// num
			// 
			this->num->BackColor = System::Drawing::Color::Gray;
			this->num->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->num->ForeColor = System::Drawing::Color::White;
			this->num->Location = System::Drawing::Point(70, 140);
			this->num->Name = L"num";
			this->num->Size = System::Drawing::Size(244, 20);
			this->num->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(70, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Введите номер дома";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(70, 121);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(188, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Введите новое число жильцов";
			// 
			// UpdateForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->num);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->cont);
			this->Controls->Add(this->number);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"UpdateForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UpdateForm";
			this->Load += gcnew System::EventHandler(this, &UpdateForm::UpdateForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void cont_Click(System::Object^ sender, System::EventArgs^ e) {

		int houseNumber;
		if (!Int32::TryParse(number->Text, houseNumber) || houseNumber < 0) {
			MessageBox::Show("Пожалуйста, введите корректный положительный номер дома.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return; 
		}

		int numResidents;
		if (!Int32::TryParse(num->Text, numResidents) || numResidents < 0) {
			MessageBox::Show("Пожалуйста, введите корректное положительное количество жильцов.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return; 
		}

		Agency^ agency = ReadFromBinaryFile("FileName.bin");

		House^ targetHouse = nullptr;
		for each (House ^ house in agency->houses) {
			if (house->number == houseNumber) {
				targetHouse = house;
				break;
			}
		}

		if (targetHouse != nullptr) {

			int currentNumResidents = targetHouse->numResidents;

			if (numResidents > currentNumResidents) {
				int diff = numResidents - currentNumResidents;
				for (int i = 0; i < diff; i++) {
					AddForm^ add = gcnew AddForm();
					add->ShowDialog();

					String^ name = add->GetName();
					int age = add->GetAge();

					// Добавить нового жильца в список residents
					Resident^ newResident = gcnew Resident();
					newResident->name = name;
					newResident->age = age;
					targetHouse->residents->Add(newResident);


					if (i < diff - 1)
						add->Close();
				}
			}
			else if (numResidents < currentNumResidents) {

				int diff = currentNumResidents - numResidents;
				for (int i = 0; i < diff; i++) {
					RemForm^ rem = gcnew RemForm();
					rem->ShowDialog();

					String^ name = rem->GetName();
					int age = rem->GetAge();

					// Удалить ненужного жильца из списка residents
					if (targetHouse->residents->Count > 0) {
						targetHouse->residents->RemoveAt(targetHouse->residents->Count - 1);
					}


					if (i < diff - 1)
						rem->Close();
				}
			}

			targetHouse->numResidents = numResidents;

			WriteToBinaryFile("FileName.bin", agency);

			this->Close();
		}

	}
	private: System::Void UpdateForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
