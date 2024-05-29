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
	/// Сводка для GetData
	/// </summary>
	public ref class GetData : public System::Windows::Forms::Form
	{
	public:
		GetData(void)
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
		~GetData()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
	private: System::Windows::Forms::RichTextBox^ displayTextBox;

	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GetData::typeid));
			this->displayTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// displayTextBox
			// 
			this->displayTextBox->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->displayTextBox->Location = System::Drawing::Point(12, 12);
			this->displayTextBox->Name = L"displayTextBox";
			this->displayTextBox->ReadOnly = true;
			this->displayTextBox->Size = System::Drawing::Size(376, 245);
			this->displayTextBox->TabIndex = 0;
			this->displayTextBox->Text = L"";
			this->displayTextBox->TextChanged += gcnew System::EventHandler(this, &GetData::displayTextBox_TextChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(68, 263);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(269, 25);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Выход";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &GetData::button1_Click);
			// 
			// GetData
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->displayTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"GetData";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DisplayForm";
			this->Load += gcnew System::EventHandler(this, &GetData::GetData_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void GetData_Load(System::Object^ sender, System::EventArgs^ e) {

		Agency^ agency = ReadFromBinaryFile("FileName.bin");

		displayTextBox->Clear();

		for each (House ^ house in agency->houses) {
			displayTextBox->AppendText("Дом номер " + house->number + Environment::NewLine);
			displayTextBox->AppendText("Количество жильцов: " + house->numResidents + Environment::NewLine);

			for each (Resident ^ resident in house->residents) {
				displayTextBox->AppendText("Имя: " + resident->name + ", Возраст: " + resident->age + Environment::NewLine);
			}

			displayTextBox->AppendText(Environment::NewLine);
		}


	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	private: System::Void displayTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
