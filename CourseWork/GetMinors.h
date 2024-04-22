#pragma once

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для GetMinors
	/// </summary>
	public ref class GetMinors : public System::Windows::Forms::Form
	{
	public:
		GetMinors(void)
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
		~GetMinors()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ minors;
	protected:
	private: System::Windows::Forms::Button^ button1;

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
			this->minors = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// minors
			// 
			this->minors->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->minors->Location = System::Drawing::Point(12, 12);
			this->minors->Name = L"minors";
			this->minors->Size = System::Drawing::Size(376, 242);
			this->minors->TabIndex = 0;
			this->minors->Text = L"";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(80, 260);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(235, 28);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Выход";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &GetMinors::button1_Click);
			// 
			// GetMinors
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->minors);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"GetMinors";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GetMinors";
			this->Load += gcnew System::EventHandler(this, &GetMinors::GetMinors_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void GetMinors_Load(System::Object^ sender, System::EventArgs^ e) {
		// Загружаем данные из файла
		Agency^ agency = ReadFromBinaryFile("FileName.bin");

		// Очищаем содержимое RichTextBox
		minors->Clear();

		// Проходим по всем домам в агентстве
		for each (House ^ house in agency->houses) {
			int minorsCount = 0;

			// Проверяем каждого жильца в доме
			for each (Resident ^ resident in house->residents) {
				// Если возраст меньше 18, увеличиваем счетчик несовершеннолетних
				if (resident->age < 18) {
					minorsCount++;
				}
			}

			// Добавляем количество несовершеннолетних для текущего дома в RichTextBox
			minors->Text += "Дом " + house->number + ": " + minorsCount + " несовершеннолетних\n";
		}
	}

	};
}
