#pragma once

#include "myclass.h"
#include "EnterForm2.h"

namespace course {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для EnterForm
	/// </summary>
public ref class EnterForm : public System::Windows::Forms::Form
{
public:
	EnterForm(void)
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
	~EnterForm()
	{
		if (components)
		{
			delete components;
		}
	}

protected:
private: System::Windows::Forms::Button^ Exit;
private: System::Windows::Forms::TextBox^ num;

private: System::Windows::Forms::TextBox^ number;

private: System::Windows::Forms::Button^ Save;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;


protected:

private:
	/// <summary>
	/// Обязательная переменная конструктора.
	/// </summary>
	System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Требуемый метод для поддержки конструктора — не изменяйте 
	/// содержимое этого метода с помощью редактора кода.
	/// </summary>
	void InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(EnterForm::typeid));
		this->Exit = (gcnew System::Windows::Forms::Button());
		this->num = (gcnew System::Windows::Forms::TextBox());
		this->number = (gcnew System::Windows::Forms::TextBox());
		this->Save = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->SuspendLayout();
		// 
		// Exit
		// 
		this->Exit->BackColor = System::Drawing::Color::Gray;
		this->Exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->Exit->ForeColor = System::Drawing::Color::White;
		this->Exit->Location = System::Drawing::Point(228, 173);
		this->Exit->Name = L"Exit";
		this->Exit->Size = System::Drawing::Size(116, 53);
		this->Exit->TabIndex = 1;
		this->Exit->Text = L"Выход";
		this->Exit->UseVisualStyleBackColor = false;
		this->Exit->Click += gcnew System::EventHandler(this, &EnterForm::Exit_Click);
		// 
		// num
		// 
		this->num->BackColor = System::Drawing::Color::Gray;
		this->num->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->num->ForeColor = System::Drawing::Color::White;
		this->num->Location = System::Drawing::Point(57, 137);
		this->num->Name = L"num";
		this->num->Size = System::Drawing::Size(287, 20);
		this->num->TabIndex = 2;
		// 
		// number
		// 
		this->number->BackColor = System::Drawing::Color::Gray;
		this->number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->number->ForeColor = System::Drawing::Color::White;
		this->number->Location = System::Drawing::Point(57, 69);
		this->number->Name = L"number";
		this->number->Size = System::Drawing::Size(287, 20);
		this->number->TabIndex = 3;
		this->number->TextChanged += gcnew System::EventHandler(this, &EnterForm::number_TextChanged);
		// 
		// Save
		// 
		this->Save->BackColor = System::Drawing::Color::Gray;
		this->Save->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->Save->ForeColor = System::Drawing::Color::White;
		this->Save->Location = System::Drawing::Point(57, 173);
		this->Save->Name = L"Save";
		this->Save->Size = System::Drawing::Size(115, 53);
		this->Save->TabIndex = 4;
		this->Save->Text = L"Сохранить";
		this->Save->UseVisualStyleBackColor = false;
		this->Save->Click += gcnew System::EventHandler(this, &EnterForm::Save_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label1->ForeColor = System::Drawing::Color::White;
		this->label1->Location = System::Drawing::Point(54, 53);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(135, 13);
		this->label1->TabIndex = 5;
		this->label1->Text = L"Введите номер дома:";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label2->ForeColor = System::Drawing::Color::White;
		this->label2->Location = System::Drawing::Point(54, 121);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(187, 13);
		this->label2->TabIndex = 6;
		this->label2->Text = L"Введите количество жильцов:";
		// 
		// EnterForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
			static_cast<System::Int32>(static_cast<System::Byte>(69)));
		this->BackgroundImage = nullptr;
		this->ClientSize = System::Drawing::Size(400, 300);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->Save);
		this->Controls->Add(this->number);
		this->Controls->Add(this->num);
		this->Controls->Add(this->Exit);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Name = L"EnterForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"EnterForm";
		this->Load += gcnew System::EventHandler(this, &EnterForm::EnterForm_Load);
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

	// Функция для проверки уникальности номера дома
	bool IsHouseNumberUnique(Agency^ agency, int houseNumber) {
		for each (House ^ house in agency->houses) {
			if (house->number == houseNumber) {
				return false; // Номер дома уже существует
			}
		}
		return true; // Номер дома уникален
	}


private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
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

	// Загружаем существующие данные из файла
	Agency^ agency = ReadFromBinaryFile("FileName.bin");

	// Проверяем, есть ли дом с таким номером уже в списке
	if (IsHouseNumberUnique(agency, houseNumber)) {
		// Создаем новый дом
		House^ newHouse = gcnew House();
		newHouse->number = houseNumber;
		newHouse->numResidents = numResidents;
		newHouse->residents = gcnew List<Resident^>();

		for (int i = 0; i < numResidents; i++) {
			EnterForm2^ enterForm2 = gcnew EnterForm2();
			enterForm2->ShowDialog();

			// Запрос имени и возраста в текущем окне
			String^ name = enterForm2->GetName();
			int age = enterForm2->GetAge();

			Resident^ resident = gcnew Resident();
			resident->name = name;
			resident->age = age;

			newHouse->residents->Add(resident);

			if (i < numResidents - 1)
				enterForm2->Close();
		}

		// Добавляем новый дом к существующим данным
		agency->houses->Add(newHouse);

		// Сохраняем все данные в файл
		WriteToBinaryFile("FileName.bin", agency);

		this->Close();
	}
	else {
		// Оповещаем пользователя о том, что дом с таким номером уже существует
		MessageBox::Show("Дом с указанным номером уже существует.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}


private: System::Void number_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Exit_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
private: System::Void EnterForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
